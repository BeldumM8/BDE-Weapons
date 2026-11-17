enum BDE_RPG7_RPC
{
    RPC_RPG7_DETONATION_FX = 69336541
}

// Server-authoritative RPG-7 rocket flight.
// DayZ handles the weapon FSM, chambering and trigger event. Once EEFired fires,
// this entity owns the rocket's flight, motor, collision, damage and self-destruct.
class BDE_RPG7_Flight extends Inventory_Base
{
    protected ref Timer m_BDEFlightTimer;
    protected ref Timer m_BDEDeleteTimer;
    protected Particle m_BDEMotorFlame;
    protected EffectSound m_BDEMotorSound;
    protected bool m_BDEIgnitionFXPlayed;

    protected vector m_BDEVelocity;
    protected Object m_BDELauncher;
    protected PlayerBase m_BDEShooter;

    protected float m_BDEAge;
    protected float m_BDEDistanceTravelled;
    protected int m_BDELastTick;
    protected float m_BDEFinPhase;
    protected bool m_BDEMotorIgnited;
    protected bool m_BDEFinished;

    void BDE_RPG7_Flight()
    {
        RegisterNetSyncVariableBool("m_BDEMotorIgnited");
        RegisterNetSyncVariableFloat("m_BDEFinPhase", 0.0, 1.0, 3);
    }

    void ~BDE_RPG7_Flight()
    {
        BDEStopMotorFX();
    }

    override void EEInit()
    {
        super.EEInit();
        BDEUpdateFlightVisuals();
        BDEUpdateMotorFX();
    }

    override void OnVariablesSynchronized()
    {
        super.OnVariablesSynchronized();
        BDEUpdateFlightVisuals();
        BDEUpdateMotorFX();
    }

    override bool IsTakeable()
    {
        return false;
    }

    override bool CanPutInCargo(EntityAI parent)
    {
        return false;
    }

    override bool CanPutIntoHands(EntityAI parent)
    {
        return false;
    }

    void BDELaunch(vector direction, Object launcher, PlayerBase shooter)
    {
        if (!GetGame().IsServer())
            return;

        direction.Normalize();

        // The PGO-7 ranging marks sit below its upper boresight cross.
        // Fixed per-round alignment; the player's selectable zero remains 0 m.
        Weapon_Base firingWeapon = Weapon_Base.Cast(launcher);
        if (firingWeapon && firingWeapon.FindAttachmentBySlotName("weaponOptics"))
        {
            // Derive signed elevation directly. VectorToAngles can wrap a
            // downward pitch near 360 degrees; clamping that launches upward.
            float horizontal = Math.Sqrt(direction[0] * direction[0] + direction[2] * direction[2]);
            if (horizontal > 0.0001)
            {
                float elevation = Math.Asin(Math.Clamp(direction[1], -1.0, 1.0));
                elevation = Math.Clamp(elevation + BDEGetScopeBoreElevation() * Math.DEG2RAD, -89.0 * Math.DEG2RAD, 89.0 * Math.DEG2RAD);
                float horizontalScale = Math.Cos(elevation) / horizontal;
                direction = Vector(direction[0] * horizontalScale, Math.Sin(elevation), direction[2] * horizontalScale);
            }
        }

        m_BDELauncher = launcher;
        m_BDEShooter = shooter;
        m_BDEVelocity = direction * BDEGetLaunchVelocity();
        m_BDEAge = 0.0;
        m_BDEDistanceTravelled = 0.0;
        m_BDEFinPhase = 0.0;
        m_BDEMotorIgnited = false;
        m_BDEFinished = false;
        m_BDELastTick = GetGame().GetTime();
        Print("[BDE_RPG7_FLIGHT] launch type=" + GetType() + " position=" + GetPosition() + " direction=" + direction);

        BDEOrientRocket(direction);
        BDEUpdateFlightVisuals();
        SetSynchDirty();
        SetAllowDamage(false);

        m_BDEFlightTimer = new Timer(CALL_CATEGORY_SYSTEM);
        m_BDEFlightTimer.Run(0.02, this, "BDETick", null, true);
    }

    void BDETick()
    {
        if (!GetGame().IsServer() || m_BDEFinished)
            return;

        int now = GetGame().GetTime();
        float remaining = (now - m_BDELastTick) * 0.001;
        m_BDELastTick = now;

        // Integrate in small chunks so a slow server frame does not let the rocket
        // tunnel through nearby geometry at high speed.
        while (remaining > 0.0 && !m_BDEFinished)
        {
            float dt = Math.Min(remaining, 0.005);
            remaining -= dt;
            BDEStep(dt);
        }
    }

    protected void BDEStep(float dt)
    {
        m_BDEAge += dt;

        if (m_BDEAge >= BDEGetSelfDestructTime())
        {
            BDEDetonate(null);
            return;
        }

        vector forward = m_BDEVelocity.Normalized();
        float speed = m_BDEVelocity.Length();

        if (m_BDEMotorIgnited && speed < BDEGetSustainerMaxVelocity())
        {
            float acceleratedSpeed = Math.Min(BDEGetSustainerMaxVelocity(), speed + BDEGetSustainerAcceleration() * dt);
            m_BDEVelocity = forward * acceleratedSpeed;
        }

        m_BDEVelocity += Vector(0, -9.81 * dt, 0);

        vector start = GetPosition();
        vector end = start + m_BDEVelocity * dt;
        // Exclude the projectile and the complete firing hierarchy up front.
        // Never step through ignored geometry: a wall beyond it must still hit.
        array<Object> excluded = new array<Object>;
        excluded.Insert(this);
        BDEExcludeHierarchy(EntityAI.Cast(m_BDELauncher), excluded);
        BDEExcludeHierarchy(m_BDEShooter, excluded);

        RaycastRVParams ray = new RaycastRVParams(start, end, this, 0.02);
        ray.type = ObjIntersectFire;
        ray.flags = CollisionFlags.ALLOBJECTS;
        array<ref RaycastRVResult> hits = new array<ref RaycastRVResult>;
        DayZPhysics.RaycastRVProxy(ray, hits, excluded);

        RaycastRVResult nearest;
        float nearestDistance = float.MAX;
        foreach (RaycastRVResult contact : hits)
        {
            // Proxy contacts can report their parent separately from the object.
            if (BDEIsLaunchHierarchy(contact.obj) || BDEIsLaunchHierarchy(contact.parent))
                continue;

            float distance = vector.DistanceSq(start, contact.pos);
            if (distance < nearestDistance)
            {
                nearest = contact;
                nearestDistance = distance;
            }
        }

        if (nearest)
        {
            EntityAI hitEntity = EntityAI.Cast(nearest.obj);
            if (!hitEntity)
                hitEntity = EntityAI.Cast(nearest.parent);

            string hitType = "terrain";
            string parentType = "none";
            if (nearest.obj)
                hitType = nearest.obj.GetType();
            if (nearest.parent)
                parentType = nearest.parent.GetType();

            m_BDEDistanceTravelled += vector.Distance(start, nearest.pos);
            Print("[BDE_RPG7_FLIGHT] impact object=" + hitType + " parent=" + parentType + " start=" + start + " end=" + end + " hit=" + nearest.pos);
            SetPosition(nearest.pos + nearest.dir.Normalized() * 0.03);
            string damageZone;
            if (hitEntity && nearest.component >= 0)
            {
                damageZone = hitEntity.GetDamageZoneNameByComponentIndex(nearest.component);
                if (damageZone == "")
                {
                    // Construction fire-geometry selections are named after their zones.
                    string selection = hitEntity.GetActionComponentName(nearest.component, "fire");
                    if (GetGame().ConfigIsExisting("CfgVehicles " + hitEntity.GetType() + " DamageSystem DamageZones " + selection))
                    {
                        damageZone = selection;
                    }
                }
            }
            BDEDetonate(hitEntity, damageZone, nearest.pos);
            return;
        }

        m_BDEDistanceTravelled += vector.Distance(GetPosition(), end);
        SetPosition(end);
        BDEOrientRocket(m_BDEVelocity.Normalized());
        BDEUpdateFinDeployment();

        if (BDEHasSustainer() && !m_BDEMotorIgnited && m_BDEDistanceTravelled >= BDEGetMotorIgnitionDistance())
            BDEIgniteMotor();
    }

    protected void BDEExcludeHierarchy(EntityAI root, array<Object> excluded)
    {
        if (!root)
            return;

        excluded.Insert(root);
        array<EntityAI> items = new array<EntityAI>;
        root.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items);
        foreach (EntityAI item : items)
        {
            excluded.Insert(item);
        }
    }

    protected bool BDEIsLaunchHierarchy(Object candidate)
    {
        if (!candidate)
            return false;

        if (candidate == this || candidate == m_BDELauncher || candidate == m_BDEShooter)
            return true;

        EntityAI entity = EntityAI.Cast(candidate);
        while (entity)
        {
            if (entity == this || entity == m_BDELauncher || entity == m_BDEShooter)
                return true;

            entity = entity.GetHierarchyParent();
        }

        return false;
    }

    protected void BDEOrientRocket(vector direction)
    {
        // Verified PG7/PG7R/OG7: booster, fins and motor lie at +X;
        // the nose is -X. This basis maps the nose onto velocity, not its inverse.
        vector up = "0 1 0";
        if (Math.AbsFloat(vector.Dot(direction, up)) > 0.99)
            up = "0 0 1";

        vector basis[4];
        Math3D.DirectionAndUpMatrix(direction, up, basis);

        vector transform[4];
        transform[0] = basis[2] * -1.0;
        transform[1] = basis[1];
        transform[2] = basis[0];
        transform[3] = GetPosition();
        SetTransform(transform);
    }

    protected void BDEUpdateFinDeployment()
    {
        float startDistance = BDEGetFinDeployDistance();
        float endDistance = BDEGetMotorIgnitionDistance();
        float phase = 0.0;

        if (m_BDEDistanceTravelled >= endDistance)
            phase = 1.0;
        else if (m_BDEDistanceTravelled > startDistance && endDistance > startDistance)
            phase = (m_BDEDistanceTravelled - startDistance) / (endDistance - startDistance);

        if (phase == m_BDEFinPhase)
            return;

        m_BDEFinPhase = phase;
        BDEUpdateFlightVisuals();
        SetSynchDirty();
    }

    protected void BDEUpdateFlightVisuals()
    {
        // Only the internal flight entity runs this; loose and chambered ammo stay folded.
        SetAnimationPhaseNow("booster_hide", 1.0);
        SetAnimationPhaseNow("fin_1_deploy", m_BDEFinPhase);
        SetAnimationPhaseNow("fin_2_deploy", m_BDEFinPhase);
        SetAnimationPhaseNow("fin_3_deploy", m_BDEFinPhase);
        SetAnimationPhaseNow("fin_4_deploy", m_BDEFinPhase);
    }

    protected void BDEIgniteMotor()
    {
        if (m_BDEMotorIgnited)
            return;

        m_BDEMotorIgnited = true;
        BDEUpdateMotorFX();
        SetSynchDirty();
    }

    protected void BDEDetonate(EntityAI directHit, string damageZone = "", vector hitPosition = "0 0 0")
    {
        if (m_BDEFinished)
            return;

        m_BDEFinished = true;
        Print("[BDE_RPG7_FLIGHT] detonate age=" + m_BDEAge + " distance=" + m_BDEDistanceTravelled + " position=" + GetPosition());

        if (m_BDEFlightTimer)
            m_BDEFlightTimer.Stop();

        vector detonationPosition = GetPosition();

        if (directHit)
            BDEDealDirectDamage(directHit, hitPosition, damageZone);

        BDEDealExplosiveDamage(detonationPosition);
        BDEBroadcastDetonationFX(detonationPosition);
        Print("[BDE_RPG7_FLIGHT] detonate-complete; deleting in 500 ms");

        BDEStopMotorFX();
        // Match the owned deletion timer used by vanilla ExplosivesBase.
        // Keep normal network-bubble membership throughout the entity's lifetime.
        m_BDEDeleteTimer = new Timer(CALL_CATEGORY_SYSTEM);
        m_BDEDeleteTimer.Run(0.5, this, "BDEDeleteProjectile");
    }

    void BDEDeleteProjectile()
    {
        Print("[BDE_RPG7_FLIGHT] cleanup type=" + GetType());
        DeleteSafe();
    }

    protected void BDEDealDirectDamage(EntityAI hitEntity, vector hitPosition, string damageZone)
    {
        if (!hitEntity || !hitEntity.GetAllowDamage())
            return;

        if (BDEIsProtectedByNinjins(hitEntity))
        {
            BDENotifyShooter("RPG direct damage blocked by Ninjins (PVE or Safezone)");
            return;
        }

        string directDamageAmmo = BDEGetDirectDamageAmmo();
        if (directDamageAmmo == string.Empty)
            return;

        EntityAI damageSource = m_BDEShooter;
        if (!damageSource)
            damageSource = EntityAI.Cast(m_BDELauncher);

        if (!damageSource)
            damageSource = this;

        vector hitPositionMS = hitEntity.WorldToModel(hitPosition);
        // Never force SetHealth(0): normal damage callbacks must enforce raid permissions.
        if (BaseBuildingBase.Cast(hitEntity) && damageZone == "")
        {
            Print("[BDE_RPG7_DAMAGE] Unresolved construction hit: target=" + hitEntity.GetType() + " ammo=" + directDamageAmmo + " position=" + hitPosition);
            return;
        }
        float healthBefore = hitEntity.GetHealth(damageZone, "Health");
        hitEntity.ProcessDirectDamage(DT_FIRE_ARM, damageSource, damageZone, directDamageAmmo, hitPositionMS);
        Print("[BDE_RPG7_DAMAGE] target=" + hitEntity.GetType() + " zone=" + damageZone + " ammo=" + directDamageAmmo + " healthBefore=" + healthBefore + " healthAfter=" + hitEntity.GetHealth(damageZone, "Health"));
    }

    protected void BDEDealExplosiveDamage(vector position)
    {
        string blastDamageAmmo = BDEGetBlastDamageAmmo();
        if (blastDamageAmmo == string.Empty)
            return;

#ifdef Ninjins_PvP_PvE_Upgraded_Zones
        float blastRange = GetGame().ConfigGetFloat("CfgAmmo " + blastDamageAmmo + " indirectHitRange");
        array<Object> nearbyObjects = new array<Object>();
        GetGame().GetObjectsAtPosition(position, blastRange + 1.0, nearbyObjects, null);

        foreach (Object nearbyObject : nearbyObjects)
        {
            if (BDEIsProtectedByNinjins(nearbyObject))
            {
                BDENotifyShooter("RPG explosive damage blocked by Ninjins (PVE or Safezone)");
                return;
            }
        }

#endif

        // The source is the exploding entity, as with vanilla grenades/mines.
        // Shooter attribution is not a substitute for the physical blast source.
        Print("[BDE_RPG7_FLIGHT] blast-begin ammo=" + blastDamageAmmo + " position=" + position);
        DamageSystem.ExplosionDamage(this, null, blastDamageAmmo, position, DamageType.EXPLOSION);
        Print("[BDE_RPG7_FLIGHT] blast-end");
    }

    protected void BDEBroadcastDetonationFX(vector position)
    {
        Param1<vector> fxData = new Param1<vector>(position);
        GetGame().RPCSingleParam(this, BDE_RPG7_RPC.RPC_RPG7_DETONATION_FX, fxData, true);
    }

    protected void BDEPlayDetonationFX(vector position)
    {
        if (!GetGame().IsClient())
            return;

        // A late motor/fin synchronization must not restart effects after impact.
        m_BDEFinished = true;
        ParticleManager.GetInstance().PlayInWorld(ParticleList.RGD5, position);

        EffectSound sound = SEffectManager.PlaySound("Grenade_explosion_SoundSet", position);
        if (sound)
            sound.SetSoundAutodestroy(true);

        ClearFlags(EntityFlags.VISIBLE, false);
        BDEStopMotorFX();
    }

    protected void BDEUpdateMotorFX()
    {
        if (!GetGame().IsClient())
            return;

        if (m_BDEFinished || !m_BDEMotorIgnited)
        {
            BDEStopMotorFX();
            return;
        }

        if (!m_BDEMotorFlame)
        {
            ParticleManager particleManager = ParticleManager.GetInstance();
            if (particleManager)
            {
                vector motorPosition = GetMemoryPointPos("motor");
                if (!m_BDEIgnitionFXPlayed)
                {
                    particleManager.PlayOnObject(ParticleList.BDE_RPG7_IGNITION, this, motorPosition);
                    m_BDEIgnitionFXPlayed = true;
                }
                m_BDEMotorFlame = particleManager.PlayOnObject(ParticleList.BDE_RPG7_MOTOR, this, motorPosition);
            }
        }

        if (!m_BDEMotorSound)
        {
            m_BDEMotorSound = SEffectManager.PlaySoundOnObject("BDE_RPG7_RocketFly_SoundSet", this, 0.02, 0.08, true);
            if (m_BDEMotorSound)
                m_BDEMotorSound.SetAutodestroy(true);
        }
    }

    protected void BDEStopMotorFX()
    {
        if (m_BDEMotorFlame)
        {
            m_BDEMotorFlame.Stop();
            m_BDEMotorFlame = null;
        }

        if (m_BDEMotorSound)
        {
            m_BDEMotorSound.SoundStop();
            m_BDEMotorSound = null;
        }
    }

    protected void BDENotifyShooter(string message)
    {
        if (!m_BDEShooter || !m_BDEShooter.GetIdentity())
            return;

        Param1<string> messageParam = new Param1<string>(message);
        GetGame().RPCSingleParam(m_BDEShooter, ERPCs.RPC_USER_ACTION_MESSAGE, messageParam, true, m_BDEShooter.GetIdentity());
    }

    protected bool BDEHasSustainer()
    {
        return true;
    }

    protected float BDEGetScopeBoreElevation()
    {
        return 0.0;
    }

    protected float BDEGetLaunchVelocity()
    {
        return 117.0;
    }

    protected float BDEGetFinDeployDistance()
    {
        return 1.0;
    }

    protected float BDEGetMotorIgnitionDistance()
    {
        return 20.0;
    }

    protected float BDEGetSustainerAcceleration()
    {
        return 900.0;
    }

    protected float BDEGetSustainerMaxVelocity()
    {
        return 300.0;
    }

    protected float BDEGetSelfDestructTime()
    {
        return 5.0;
    }

    protected string BDEGetDirectDamageAmmo()
    {
        return string.Empty;
    }

    protected string BDEGetBlastDamageAmmo()
    {
        return "BDE_RPG7_Blast_OG7";
    }

    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        super.OnRPC(sender, rpc_type, ctx);

        if (rpc_type == BDE_RPG7_RPC.RPC_RPG7_DETONATION_FX && GetGame().IsClient())
        {
            Param1<vector> fxData;

            if (ctx.Read(fxData))
                BDEPlayDetonationFX(fxData.param1);
        }
    }

    override void EEDelete(EntityAI parent)
    {
        if (m_BDEFlightTimer)
            m_BDEFlightTimer.Stop();

        if (m_BDEDeleteTimer)
            m_BDEDeleteTimer.Stop();

        BDEStopMotorFX();
        if (GetGame().IsServer())
            Print("[BDE_RPG7_FLIGHT] EEDelete begin type=" + GetType());

        super.EEDelete(parent);

        if (GetGame().IsServer())
            Print("[BDE_RPG7_FLIGHT] EEDelete end type=" + GetType());
    }

    bool BDEIsProtectedByNinjins(Object targetObject)
    {
#ifdef Ninjins_PvP_PvE_Upgraded_Zones
        if (!targetObject || targetObject == this)
            return false;

        // Generic invulnerability is not evidence of a Ninjins zone.
        EntityAI hitEntity = EntityAI.Cast(targetObject);
        PlayerBase targetPlayer = PlayerBase.Cast(targetObject);
        if (!targetPlayer && hitEntity)
            targetPlayer = PlayerBase.Cast(hitEntity.GetHierarchyRootPlayer());

        if (targetPlayer && (targetPlayer.NinjinsUpgraded_IsInSafeZone() || targetPlayer.NinjinsUpgraded_IsInPvEZone() || targetPlayer.NinjinsUpgraded_SafeExitActive()))
            return true;

        // PvE zones still permit fighting infected and wildlife. The rocket
        // itself (and non-damageable world objects) cannot be a protected target.
        bool pveCombatTarget = !hitEntity || targetObject == this || hitEntity.IsKindOf("DayZInfected") || hitEntity.IsKindOf("AnimalBase");
        if (BDEIsPositionInNinjinProtectedZone(targetObject.GetPosition(), pveCombatTarget))
            return true;

        Transport targetVehicle = BDEGetRootTransport(targetObject);
        if (targetVehicle && BDEIsPositionInNinjinProtectedZone(targetVehicle.GetPosition()))
            return true;
#endif
        return false;
    }

#ifdef Ninjins_PvP_PvE_Upgraded_Zones
    protected bool BDEIsPositionInNinjinProtectedZone(vector position, bool ignorePve = false)
    {
        NinjinsUpgraded_ZoneEngine engine = NinjinsUpgraded_ZoneEngineModule.GetEngine();
        if (!engine)
            return false;
        if (engine.NinjinsUpgraded_IsWorldPositionInActiveSafeZone(position))
            return true;
        if (ignorePve)
            return false;
        bool inPvp;
        bool inPve;
        engine.NinjinsUpgraded_FootprintPvpPveAtWorld(position, inPvp, inPve);
        return inPve;
    }

    protected Transport BDEGetRootTransport(Object object)
    {
        if (!object)
            return null;

        Transport directTransport = Transport.Cast(object);
        if (directTransport)
            return directTransport;

        EntityAI entity = EntityAI.Cast(object);
        if (!entity)
            return null;

        EntityAI parent = EntityAI.Cast(entity.GetHierarchyParent());

        while (parent)
        {
            Transport parentTransport = Transport.Cast(parent);

            if (parentTransport)
                return parentTransport;

            parent = EntityAI.Cast(parent.GetHierarchyParent());
        }

        return null;
    }
#endif
}

class BDE_RPG7_Flight_OG7 extends BDE_RPG7_Flight
{
    // Game calibration for the fixed 0.15704-radian PGO-7 view.
    override protected float BDEGetLaunchVelocity()
    {
        return 152.794294;
    }

    override protected float BDEGetScopeBoreElevation()
    {
        return 2.264529;
    }

    override protected bool BDEHasSustainer()
    {
        return false;
    }

    override protected string BDEGetBlastDamageAmmo()
    {
        return "BDE_RPG7_Blast_OG7";
    }
}

class BDE_RPG7_Flight_PG7 extends BDE_RPG7_Flight
{
    // Game calibration for the fixed 0.15704-radian PGO-7 view.
    override protected float BDEGetLaunchVelocity()
    {
        return 177.871452;
    }

    override protected float BDEGetScopeBoreElevation()
    {
        return 2.078680;
    }

    override protected float BDEGetSustainerMaxVelocity()
    {
        return 276.688715;
    }

    override protected string BDEGetDirectDamageAmmo()
    {
        return "BDE_RPG7_Direct_PG7";
    }

    override protected string BDEGetBlastDamageAmmo()
    {
        return "BDE_RPG7_Blast_PG7";
    }
}

class BDE_RPG7_Flight_PG7R extends BDE_RPG7_Flight
{
    // Game calibration for the fixed 0.15704-radian PGO-7 view.
    override protected float BDEGetLaunchVelocity()
    {
        return 90.868964;
    }

    override protected float BDEGetScopeBoreElevation()
    {
        return 1.740978;
    }

    override protected float BDEGetSustainerMaxVelocity()
    {
        return 146.252635;
    }

    override protected string BDEGetDirectDamageAmmo()
    {
        return "BDE_RPG7_Direct_PG7R";
    }

    override protected string BDEGetBlastDamageAmmo()
    {
        return "BDE_RPG7_Blast_PG7R";
    }

}
