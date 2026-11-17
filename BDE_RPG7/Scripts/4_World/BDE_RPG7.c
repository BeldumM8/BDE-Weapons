enum BDE_RPG7_AnimState
{
    DEFAULT = 0
}

enum BDE_RPG7_StableStateID
{
    UNKNOWN = 0,
    Empty = 1,
    Loaded = 2
}

class BDE_RPG7_Empty extends WeaponStableState
{
    override int GetCurrentStateID()
    {
        return BDE_RPG7_StableStateID.Empty;
    }

    override bool HasBullet()
    {
        return false;
    }

    override bool HasMagazine()
    {
        return false;
    }

    override bool IsJammed()
    {
        return false;
    }

    override bool IsRepairEnabled()
    {
        return true;
    }

    override void InitMuzzleArray()
    {
        m_muzzleHasBullet = {MuzzleState.E};
    }
}

class BDE_RPG7_Loaded extends WeaponStableState
{
    override int GetCurrentStateID()
    {
        return BDE_RPG7_StableStateID.Loaded;
    }

    override bool HasBullet()
    {
        return true;
    }

    override bool HasMagazine()
    {
        return false;
    }

    override bool IsJammed()
    {
        return false;
    }

    override bool IsRepairEnabled()
    {
        return true;
    }

    override void InitMuzzleArray()
    {
        m_muzzleHasBullet = {MuzzleState.L};
    }
}

// This state changes presentation only. Vanilla OnEntry, OnExit and OnAbort
// own cartridge acquisition, chamber insertion, cancellation and dropped ammo.
class BDE_RPG7_ReloadCartridge extends WeaponChambering_Cartridge
{
    override bool AcquireCartridgeFromMagazine()
    {
        BDE_RPG7 launcher = BDE_RPG7.Cast(m_weapon);
        launcher.BDETraceReload("acquire-before", m_srcMagazine);
        bool acquired = super.AcquireCartridgeFromMagazine();
        Print("[BDE_RPG7_RELOAD] acquired=" + acquired + " cartridge=" + m_type);
        launcher.BDETraceReload("acquire-after", m_srcMagazine);
        return acquired;
    }

    override bool PushBulletToChamber(int muzzleIndex)
    {
        bool inserted = super.PushBulletToChamber(muzzleIndex);
        BDE_RPG7 launcher = BDE_RPG7.Cast(m_weapon);
        Print("[BDE_RPG7_RELOAD] inserted=" + inserted + " cartridge=" + m_type);
        launcher.BDETraceReload("insert-after", m_srcMagazine);
        return inserted;
    }

    override bool ShowBullet(int muzzleIndex)
    {
        // The P3D contains the loaded rockets; no native EffectBullet is needed.
        return m_srcMagazine != null;
    }
}

// Keep vanilla inventory reservation/movement, transfer and persistence hooks.
// Recreate its submachine solely to install the presentation-only state above.
class BDE_RPG7_Reload extends WeaponChambering
{
    override void OnEntry(WeaponEventBase e)
    {
        super.OnEntry(e);
        if (e)
            BDE_RPG7.Cast(m_weapon).BDEStartReloadPresentation(1, e.m_magazine);
    }

    override void OnExit(WeaponEventBase e)
    {
        super.OnExit(e);
        BDE_RPG7.Cast(m_weapon).BDEStopReloadPresentation();
    }

    override void OnAbort(WeaponEventBase e)
    {
        super.OnAbort(e);
        BDE_RPG7.Cast(m_weapon).BDEStopReloadPresentation();
    }

    void BDE_RPG7_Reload(Weapon_Base w = null, WeaponStateBase parent = null, WeaponActions action = WeaponActions.NONE, int actionType = -1)
    {
        m_chamber = new BDE_RPG7_ReloadCartridge(m_weapon, this);

        WeaponEventBase finished = new WeaponEventHumanCommandActionFinished;
        WeaponEventBase shown = new WeaponEventAnimBulletShow;
        WeaponEventBase inserted = new WeaponEventAnimBulletInChamber;
        WeaponEventBase ejected = new WeaponEventAnimBulletEject;
        WeaponEventBase cocked = new WeaponEventAnimCocked;

        m_fsm = new WeaponFSM(this);
        m_fsm.AddTransition(new WeaponTransition(m_start, ejected, m_eject));
        m_fsm.AddTransition(new WeaponTransition(m_start, cocked, m_onCK));
        m_fsm.AddTransition(new WeaponTransition(m_start, shown, m_chamber));
        m_fsm.AddTransition(new WeaponTransition(m_onCK, ejected, m_eject));
        m_fsm.AddTransition(new WeaponTransition(m_onCK, shown, m_chamber));
        m_fsm.AddTransition(new WeaponTransition(m_eject, shown, m_chamber));
        m_fsm.AddTransition(new WeaponTransition(m_chamber, inserted, m_w4t));
        m_fsm.AddTransition(new WeaponTransition(m_w4t, finished, null));

        // Animation completion must also terminate a partially played action.
        m_fsm.AddTransition(new WeaponTransition(m_chamber, finished, null));
        m_fsm.AddTransition(new WeaponTransition(m_eject, finished, null));
        m_fsm.AddTransition(new WeaponTransition(m_onCK, finished, null));
        m_fsm.AddTransition(new WeaponTransition(m_start, finished, null));
        m_fsm.SetInitialState(m_start);
    }
}

class BDE_RPG7 extends Rifle_Base
{
    protected ref BDE_RPG7_ReloadVisual m_BDEReloadVisual;
    protected int m_BDEReloadMode;
    protected int m_BDEReloadRocket;
    protected int m_BDEReloadSerial;
    protected int m_BDESeenReloadSerial;
    protected float m_BDEReloadFrame;
    protected int m_BDEReloadStarted;

    protected ref Timer m_BDEVisualTimer;
    protected int m_BDELoadedRocket;
    protected const int BDE_RPC_BACKBLAST = 69336544;
    protected const int BDE_RPC_MUZZLE_REQUEST = 69336542;
    protected const int BDE_RPC_MUZZLE_REPLY = 69336543;
    protected ref Timer m_BDEMuzzleTimer;
    protected int m_BDEShotId;
    protected string m_BDEPendingFlight;
    protected PlayerBase m_BDEPendingShooter;
    protected vector m_BDEPendingDirection;
    protected vector m_BDEPendingMuzzle;
    protected vector m_BDEClientMuzzle;
    protected vector m_BDEClientBreech;
    protected int m_BDEClientShotTime;
    protected bool m_BDEClientShotCaptured;

    void BDE_RPG7()
    {
        RegisterNetSyncVariableInt("m_BDELoadedRocket", 0, 3);
        RegisterNetSyncVariableInt("m_BDEReloadMode", 0, 2);
        RegisterNetSyncVariableInt("m_BDEReloadRocket", 0, 3);
        RegisterNetSyncVariableInt("m_BDEReloadSerial");
        RegisterNetSyncVariableFloat("m_BDEReloadFrame", 0, 160, 1);
    }

    override void InitStateMachine()
    {
        m_abilities.Insert(new AbilityRecord(WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_ONEBULLET_CLOSED));
        m_abilities.Insert(new AbilityRecord(WeaponActions.MECHANISM, WeaponActionMechanismTypes.MECHANISM_CLOSED));
        m_abilities.Insert(new AbilityRecord(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_NORMAL));
        m_abilities.Insert(new AbilityRecord(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_COCKED));

        // Preserve the stable IDs used by existing saved launchers.
        WeaponStableState empty = new BDE_RPG7_Empty(this, null, BDE_RPG7_AnimState.DEFAULT);
        WeaponStableState loaded = new BDE_RPG7_Loaded(this, null, BDE_RPG7_AnimState.DEFAULT);
        WeaponChambering reload = new BDE_RPG7_Reload(this, null, WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_ONEBULLET_CLOSED);
        WeaponEjectBullet unload = new BDE_RPG7_Unload(this, null, WeaponActions.MECHANISM, WeaponActionMechanismTypes.MECHANISM_CLOSED);
        WeaponFire fire = new WeaponFire(this, null, WeaponActions.FIRE, WeaponActionFireTypes.FIRE_NORMAL);
        WeaponDryFire dryFire = new WeaponDryFire(this, null, WeaponActions.FIRE, WeaponActionFireTypes.FIRE_COCKED);

        WeaponEventBase loadEvent = new WeaponEventLoad1Bullet;
        WeaponEventBase unloadEvent = new WeaponEventMechanism;
        WeaponEventBase trigger = new WeaponEventTrigger;
        WeaponEventBase finished = new WeaponEventHumanCommandActionFinished;
        WeaponEventBase aborted = new WeaponEventHumanCommandActionAborted;
        WeaponEventBase timeout = new WeaponEventDryFireTimeout;

        m_fsm = new WeaponFSM();

        // Vanilla cartridge transfer decides whether a round was inserted.
        // Root abort transitions let the native submachine finish its cleanup.
        m_fsm.AddTransition(new WeaponTransition(empty, loadEvent, reload));
        m_fsm.AddTransition(new WeaponTransition(reload, finished, empty, null, new WeaponGuardCurrentChamberEmpty(this)));
        m_fsm.AddTransition(new WeaponTransition(reload, finished, loaded));
        m_fsm.AddTransition(new WeaponTransition(reload, aborted, empty, null, new WeaponGuardCurrentChamberEmpty(this)));
        m_fsm.AddTransition(new WeaponTransition(reload, aborted, loaded));

        // Vanilla ejection returns the cartridge to inventory or the ground.
        m_fsm.AddTransition(new WeaponTransition(loaded, unloadEvent, unload));
        m_fsm.AddTransition(new WeaponTransition(unload, finished, empty, null, new WeaponGuardCurrentChamberEmpty(this)));
        m_fsm.AddTransition(new WeaponTransition(unload, finished, loaded));
        m_fsm.AddTransition(new WeaponTransition(unload, aborted, empty, null, new WeaponGuardCurrentChamberEmpty(this)));
        m_fsm.AddTransition(new WeaponTransition(unload, aborted, loaded));

        // A cancelled trigger must retain a live round if no shot occurred.
        m_fsm.AddTransition(new WeaponTransition(loaded, trigger, fire));
        m_fsm.AddTransition(new WeaponTransition(fire, finished, empty, null, new WeaponGuardCurrentChamberEmpty(this)));
        m_fsm.AddTransition(new WeaponTransition(fire, finished, loaded));
        m_fsm.AddTransition(new WeaponTransition(fire, aborted, empty, null, new WeaponGuardCurrentChamberEmpty(this)));
        m_fsm.AddTransition(new WeaponTransition(fire, aborted, loaded));

        m_fsm.AddTransition(new WeaponTransition(empty, trigger, dryFire));
        m_fsm.AddTransition(new WeaponTransition(dryFire, finished, empty));
        m_fsm.AddTransition(new WeaponTransition(dryFire, aborted, empty));
        m_fsm.AddTransition(new WeaponTransition(dryFire, timeout, empty));

        SetInitialState(empty);
        m_fsm.Start();
    }

    override float GetChanceToJam()
    {
        return 0.0;
    }

    // Read-only event tracing: no timer, RPC, cartridge or count mutation.
    void BDEStartReloadPresentation(int mode, Magazine source)
    {
        PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());
        if (!GetGame().IsServer() && player != GetGame().GetPlayer())
            return;

        string type;
        if (mode == 1 && source)
            type = source.GetType();
        else if (mode == 2 && !IsChamberEmpty(0))
        {
            float damage;
            GetCartridgeInfo(0, damage, type);
        }
        type.ToLower();
        int rocket;
        if (type == "bde_ammo_og7" || type == "bde_rpg7_shot_og7")
            rocket = 1;
        else if (type == "bde_ammo_pg7" || type == "bde_rpg7_shot_pg7")
            rocket = 2;
        else if (type == "bde_ammo_pg7r" || type == "bde_rpg7_shot_pg7r")
            rocket = 3;
        if (rocket == 0)
            return;

        if (GetGame().IsServer())
        {
            m_BDEReloadMode = mode;
            m_BDEReloadRocket = rocket;
            m_BDEReloadFrame = 0;
            m_BDEReloadStarted = GetGame().GetTime();
            m_BDEReloadSerial++;
            SetSynchDirty();
        }

        if (!GetGame().IsDedicatedServer())
            BDECreateReloadPresentation(mode, rocket, 0);
    }

    void BDECreateReloadPresentation(int mode, int rocket, float frame)
    {
        if (m_BDEReloadVisual)
            m_BDEReloadVisual.Stop();
        m_BDEReloadVisual = new BDE_RPG7_ReloadVisual(this, mode, rocket, frame);
    }

    void BDEStopReloadPresentation()
    {
        if (m_BDEReloadVisual)
        {
            m_BDEReloadVisual.Stop();
            m_BDEReloadVisual = null;
        }
        if (GetGame().IsServer() && m_BDEReloadMode != 0)
        {
            m_BDEReloadMode = 0;
            m_BDEReloadFrame = 0;
            m_BDEReloadSerial++;
            SetSynchDirty();
        }
        BDEUpdateVisuals();
    }

    void BDESyncReloadPresentation()
    {
        if (GetGame().IsDedicatedServer())
            return;

        bool changed = m_BDESeenReloadSerial != m_BDEReloadSerial;
        m_BDESeenReloadSerial = m_BDEReloadSerial;
        if (m_BDEReloadMode == 0)
        {
            if (changed && m_BDEReloadVisual)
            {
                m_BDEReloadVisual.Stop();
                m_BDEReloadVisual = null;
            }
            return;
        }

        if (!m_BDEReloadVisual || !m_BDEReloadVisual.Matches(m_BDEReloadMode, m_BDEReloadRocket))
        {
            // A stopped action must not be resurrected by its last clock update.
            if (changed)
                BDECreateReloadPresentation(m_BDEReloadMode, m_BDEReloadRocket, m_BDEReloadFrame);
        }
        else
        {
            PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());
            if (player != GetGame().GetPlayer())
                m_BDEReloadVisual.CorrectFrame(m_BDEReloadFrame);
        }
    }

    void BDETickReloadPresentation()
    {
        if (!GetGame().IsServer() || m_BDEReloadMode == 0)
            return;

        PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());
        float frame = (GetGame().GetTime() - m_BDEReloadStarted) * 0.03;
        if (!player || !player.IsAlive() || player.IsUnconscious() || player.GetHumanInventory().GetEntityInHands() != this || frame > 160.0)
        {
            m_BDEReloadMode = 0;
            m_BDEReloadSerial++;
        }
        else
        {
            m_BDEReloadFrame = frame;
        }
        SetSynchDirty();
    }

    void BDETraceReload(string label, Magazine source = null)
    {
        string side = "CLIENT";
        if (GetGame().IsServer())
            side = "SERVER";

        string stateName = "none";
        WeaponStateBase state = GetCurrentState();
        if (state)
        {
            stateName = state.Type().ToString();
            while (state.HasFSM() && state.GetFSM().IsRunning())
            {
                state = state.GetFSM().GetCurrentState();
                if (!state)
                    break;
                stateName += "/" + state.Type().ToString();
            }
        }

        string sourceType = "none";
        int sourceCount = -1;
        if (source && !source.IsSetForDeletion())
        {
            sourceType = source.GetType();
            sourceCount = source.GetAmmoCount();
        }

        float damage;
        string cartridge;
        bool full = IsChamberFull(0);
        if (full)
            GetCartridgeInfo(0, damage, cartridge);

        Print("[BDE_RPG7_RELOAD] " + side + " " + label + " state=" + stateName + " full=" + full + " fired=" + IsChamberFiredOut(0) + " cartridge=" + cartridge + " source=" + sourceType + " count=" + sourceCount);
    }

    override bool ProcessWeaponEvent(WeaponEventBase e)
    {
        BDETraceReload("before " + e.Type().ToString(), e.m_magazine);
        bool accepted = super.ProcessWeaponEvent(e);
        BDETraceReload("after " + e.Type().ToString() + " accepted=" + accepted);
        return accepted;
    }

    override bool ProcessWeaponAbortEvent(WeaponEventBase e)
    {
        BDETraceReload("abort-before " + e.Type().ToString(), e.m_magazine);
        bool accepted = super.ProcessWeaponAbortEvent(e);
        BDETraceReload("abort-after " + e.Type().ToString() + " accepted=" + accepted);
        return accepted;
    }

    override void EEInit()
    {
        super.EEInit();

        m_BDEVisualTimer = new Timer(CALL_CATEGORY_SYSTEM);
        m_BDEVisualTimer.Run(0.1, this, "BDEUpdateVisuals", null, true);

        BDEUpdateVisuals();

        if (GetGame().IsServer())
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDEEnsureSights, 250, false);
    }

    override void EEDelete(EntityAI parent)
    {
        if (m_BDEReloadVisual)
        {
            m_BDEReloadVisual.Stop();
            m_BDEReloadVisual = null;
        }

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDEEnsureSights);

        if (m_BDEVisualTimer)
            m_BDEVisualTimer.Stop();

        if (m_BDEMuzzleTimer)
            m_BDEMuzzleTimer.Stop();

        m_BDEPendingFlight = "";
        m_BDEPendingShooter = null;
        super.EEDelete(parent);
    }

    override void EEOnAfterLoad()
    {
        super.EEOnAfterLoad();

        BDEUpdateVisuals();

        if (GetGame().IsServer())
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDEEnsureSights, 250, false);
    }

    override void OnVariablesSynchronized()
    {
        super.OnVariablesSynchronized();
        BDESyncReloadPresentation();
        BDEUpdateVisuals();
    }

    // The RPG model uses three built-in rocket selections instead of DayZ's
    // generic chamber-effect proxy. Do not ask the engine to instantiate an
    // EffectBullet object when FSM state is synchronized; that was the loaded
    // debug-spawn server crash in Weapon_Base.ForceSyncSelectionState().
    override void ForceSyncSelectionState()
    {
        BDEUpdateVisuals();
    }

    // This launcher has no native chamber proxy. Any generic weapon sync path
    // must update our three P3D rocket selections instead of creating an
    // EffectBullet from the chambered firing-token ammo.
    override void SyncSelectionState(bool has_bullet, bool has_mag)
    {
        BDEUpdateVisuals();
    }

    void BDEEnsureSights()
    {
        if (!GetGame().IsServer() || IsSetForDeletion())
            return;

        if (!FindAttachmentBySlotName("BDE_RPG7_Sights"))
            GetInventory().CreateAttachment("RPG7_Sights");

        BDEUpdateVisuals();
    }

    override bool CanDisplayAttachmentSlot(int slot_id)
    {
        if (InventorySlots.GetSlotName(slot_id) == "BDE_RPG7_Sights")
            return false;

        return super.CanDisplayAttachmentSlot(slot_id);
    }

    override bool CanReleaseAttachment(EntityAI attachment)
    {
        if (attachment && attachment.IsInherited(RPG7_Sights))
            return false;

        return super.CanReleaseAttachment(attachment);
    }

    override bool ShootsExplosiveAmmo()
    {
        return true;
    }

    override RecoilBase SpawnRecoilObject()
    {
        return new Izh18Recoil(this);
    }

    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (!super.CanReceiveAttachment(attachment, slotId))
            return false;

        return attachment.IsInherited(RPG7_Bipod) || attachment.IsInherited(RPG7_Sights) || attachment.IsInherited(RPG7_Optic);
    }

    void BDEUpdateVisuals()
    {
        BDETickReloadPresentation();

        // Only the server derives the selection from the native chamber.
        // Clients use the replicated value instead of a locally stale chamber.
        if (GetGame().IsServer())
        {
            int loadedRocket = 0;
            if (!IsChamberEmpty(0) && !IsChamberFiredOut(0))
            {
                float cartridgeDamage;
                string ammoType;
                GetCartridgeInfo(0, cartridgeDamage, ammoType);
                ammoType.ToLower();
                if (ammoType == "bde_rpg7_shot_og7")
                    loadedRocket = 1;
                else if (ammoType == "bde_rpg7_shot_pg7")
                    loadedRocket = 2;
                else if (ammoType == "bde_rpg7_shot_pg7r")
                    loadedRocket = 3;
            }

            if (m_BDELoadedRocket != loadedRocket)
            {
                m_BDELoadedRocket = loadedRocket;
                SetSynchDirty();
            }
        }

        int displayedRocket = m_BDELoadedRocket;
        if (m_BDEReloadVisual)
            displayedRocket = m_BDEReloadVisual.DisplayedRocket(displayedRocket);
        SetSimpleHiddenSelectionState(0, displayedRocket == 1);
        SetSimpleHiddenSelectionState(1, displayedRocket == 2);
        SetSimpleHiddenSelectionState(2, displayedRocket == 3);

        if (!GetGame().IsServer())
            return;

        RPG7_Sights sights = RPG7_Sights.Cast(FindAttachmentBySlotName("BDE_RPG7_Sights"));
        if (!sights)
            return;

        bool held = false;
        PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());

        if (player)
            held = player.GetHumanInventory().GetEntityInHands() == this;

        bool folded = !held;
        sights.BDESetFolded(folded, folded);
    }

    override void OnFire(int muzzle_index)
    {
        super.OnFire(muzzle_index);
        // Rockets leave no cartridge case in the tube.
        EjectCasing(muzzle_index);
        BDEUpdateVisuals();
    }

    protected string BDEGetFlightClass(string ammoType)
    {
        string flightClass;

        ammoType.ToLower();
        switch (ammoType)
        {
            case "bde_rpg7_shot_og7":
                flightClass = "BDE_RPG7_Flight_OG7";
                break;

            case "bde_rpg7_shot_pg7":
                flightClass = "BDE_RPG7_Flight_PG7";
                break;

            case "bde_rpg7_shot_pg7r":
                flightClass = "BDE_RPG7_Flight_PG7R";
                break;

            default:
                return "";
        }

        return flightClass;
    }

    override void EEFired(int muzzleType, int mode, string ammoType)
    {
        super.EEFired(muzzleType, mode, ammoType);

        BDEUpdateVisuals();

        PlayerBase localShooter = PlayerBase.Cast(GetHierarchyRootPlayer());
        if (GetGame().IsClient() && localShooter && localShooter == GetGame().GetPlayer())
        {
            BDEGetRenderedMuzzlePositions(m_BDEClientMuzzle, m_BDEClientBreech);
            m_BDEClientShotTime = GetGame().GetTime();
            m_BDEClientShotCaptured = true;
        }

        if (!GetGame().IsServer())
            return;

        string flightClass = BDEGetFlightClass(ammoType);
        if (flightClass == "")
            return;

        vector muzzlePosition = ModelToWorld(GetMemoryPointPos("usti hlavne"));
        vector breechPosition = ModelToWorld(GetMemoryPointPos("konec hlavne"));
        vector launchDirection = vector.Direction(breechPosition, muzzlePosition);
        // Use the same aiming angles as vanilla Weapon_Base.LiftWeaponCheckEx.
        // The animated weapon pose on the server can differ from the firing aim.
        PlayerBase shooter = PlayerBase.Cast(GetHierarchyRootPlayer());
        if (shooter)
        {
            HumanCommandWeapons weaponCommand = shooter.GetCommandModifier_Weapons();
            if (weaponCommand)
            {
                vector aimAngles = Vector(weaponCommand.GetBaseAimingAngleLR() + shooter.GetOrientation()[0], weaponCommand.GetBaseAimingAngleUD(), 0.0);
                aimAngles[0] = aimAngles[0] + weaponCommand.GetAimingHandsOffsetLR();
                aimAngles[1] = Math.Clamp(aimAngles[1] + weaponCommand.GetAimingHandsOffsetUD(), DayZPlayerCamera1stPerson.CONST_UD_MIN, DayZPlayerCamera1stPerson.CONST_UD_MAX);
                launchDirection = aimAngles.AnglesToVector();
            }
        }

        launchDirection.Normalize();
        if (m_BDEPendingFlight != "")
            BDEMuzzleTimeout();

        m_BDEShotId++;
        m_BDEPendingFlight = flightClass;
        m_BDEPendingShooter = shooter;
        m_BDEPendingDirection = launchDirection;
        m_BDEPendingMuzzle = muzzlePosition;

        if (!GetGame().IsMultiplayer() || !shooter || !shooter.GetIdentity())
        {
            BDECompletePendingShot(muzzlePosition);
            return;
        }

        // Only a server-confirmed EEFired can open a pending shot.
        m_BDEMuzzleTimer = new Timer(CALL_CATEGORY_SYSTEM);
        m_BDEMuzzleTimer.Run(1.0, this, "BDEMuzzleTimeout");
        Param1<int> request = new Param1<int>(m_BDEShotId);
        GetGame().RPCSingleParam(this, BDE_RPC_MUZZLE_REQUEST, request, true, shooter.GetIdentity());
    }

    protected void BDEGetRenderedMuzzlePositions(out vector muzzle, out vector breech)
    {
        // Same local-to-world calculation as BDE_UnderSlungLaunchers.
        // These points belong to the RPG itself, so no attachment offset is needed.
        vector weaponTransform[4];
        GetRenderTransform(weaponTransform);
        vector muzzleLocal = GetMemoryPointPos("usti hlavne");
        vector breechLocal = GetMemoryPointPos("konec hlavne");
        muzzle = muzzleLocal.Multiply4(weaponTransform);
        breech = breechLocal.Multiply4(weaponTransform);
    }

    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        super.OnRPC(sender, rpc_type, ctx);
        if (rpc_type == BDE_RPC_BACKBLAST && GetGame().IsClient())
        {
            BDE_RPG7_LaunchFX.Backblast(this);
            return;
        }


        if (rpc_type == BDE_RPC_MUZZLE_REQUEST && GetGame().IsClient())
        {
            PlayerBase localPlayer = PlayerBase.Cast(GetGame().GetPlayer());
            if (!localPlayer || localPlayer.GetHumanInventory().GetEntityInHands() != this)
                return;

            Param1<int> request;
            if (!ctx.Read(request))
                return;

            vector muzzle;
            vector breech;
            BDEGetRenderedMuzzlePositions(muzzle, breech);
            if (m_BDEClientShotCaptured && GetGame().GetTime() - m_BDEClientShotTime <= 1000)
            {
                muzzle = m_BDEClientMuzzle;
                breech = m_BDEClientBreech;
            }

            m_BDEClientShotCaptured = false;
            Param3<int, vector, vector> reply = new Param3<int, vector, vector>(request.param1, muzzle, breech);
            GetGame().RPCSingleParam(this, BDE_RPC_MUZZLE_REPLY, reply, true);
            return;
        }

        if (rpc_type != BDE_RPC_MUZZLE_REPLY || !GetGame().IsServer())
            return;

        if (!sender || m_BDEPendingFlight == "" || !m_BDEPendingShooter)
            return;

        PlayerIdentity owner = m_BDEPendingShooter.GetIdentity();
        if (!owner || sender.GetId() != owner.GetId())
            return;

        if (m_BDEPendingShooter.GetHumanInventory().GetEntityInHands() != this)
            return;

        Param3<int, vector, vector> shot;
        if (!ctx.Read(shot) || shot.param1 != m_BDEShotId)
            return;

        // Negated bounds also reject NaN/infinite coordinates.
        float muzzleDistance = vector.Distance(shot.param2, m_BDEPendingShooter.GetPosition());
        float breechDistance = vector.Distance(shot.param3, m_BDEPendingShooter.GetPosition());
        float barrelLength = vector.Distance(shot.param2, shot.param3);
        float expectedLength = vector.Distance(GetMemoryPointPos("usti hlavne"), GetMemoryPointPos("konec hlavne"));
        if (!(muzzleDistance <= 3.0) || !(breechDistance <= 3.0) || !(Math.AbsFloat(barrelLength - expectedLength) <= 0.03))
        {
            Print("[BDE_RPG7] Rejected invalid client muzzle for shot=" + m_BDEShotId);
            return;
        }

        // Position and direction must come from the same rendered weapon pose.
        // Do not combine the client muzzle with the server's animated aim vector.
        vector barrelDirection = vector.Direction(shot.param3, shot.param2);
        barrelDirection.Normalize();
        Print("[BDE_RPG7] Accepted client barrel shot=" + m_BDEShotId + " muzzle=" + shot.param2 + " direction=" + barrelDirection + " previous server direction=" + m_BDEPendingDirection);
        m_BDEPendingDirection = barrelDirection;
        BDECompletePendingShot(shot.param2);
    }

    void BDEMuzzleTimeout()
    {
        if (!GetGame().IsServer() || m_BDEPendingFlight == "")
            return;

        // Do not lose a consumed round if its owner disconnects or cannot reply.
        Print("[BDE_RPG7] Muzzle reply timeout shot=" + m_BDEShotId + "; using server memory point");
        BDECompletePendingShot(m_BDEPendingMuzzle);
    }

    protected void BDECompletePendingShot(vector muzzlePosition)
    {
        if (!GetGame().IsServer() || m_BDEPendingFlight == "")
            return;

        string flightClass = m_BDEPendingFlight;
        PlayerBase shooter = m_BDEPendingShooter;
        vector launchDirection = m_BDEPendingDirection;
        // Consume the authorization before creation: duplicates cannot spawn rockets.
        m_BDEPendingFlight = "";
        m_BDEPendingShooter = null;
        if (m_BDEMuzzleTimer)
            m_BDEMuzzleTimer.Stop();

        BDE_RPG7_Flight rocket = BDE_RPG7_Flight.Cast(GetGame().CreateObjectEx(flightClass, muzzlePosition, ECE_NOLIFETIME | ECE_KEEPHEIGHT | ECE_NOSURFACEALIGN));
        if (!rocket)
        {
            Print("[BDE_RPG7] ERROR: Could not create " + flightClass);
            return;
        }

        rocket.SetPosition(muzzlePosition);
        rocket.BDELaunch(launchDirection, this, shooter);
        // The accepted muzzle and barrel direction describe the same shot pose.
        // Backblast lies on the barrel axis behind the muzzle in this model.
        float rearOffset = vector.Distance(GetMemoryPointPos("usti hlavne"), GetMemoryPointPos("backblast"));
        vector rearPosition = muzzlePosition - launchDirection * rearOffset;
        BDE_RPG7_BackblastDamage.Apply(rearPosition, launchDirection * -1.0, this, shooter, rocket);
        if (GetGame().IsMultiplayer())
        {
            GetGame().RPCSingleParam(this, BDE_RPC_BACKBLAST, new Param1<int>(m_BDEShotId), true);
        }
        else
        {
            BDE_RPG7_LaunchFX.Backblast(this);
        }
    }

    override void OnDebugSpawn()
    {
        BDEEnsureSights();
        GetInventory().CreateAttachment("RPG7_Bipod");

        if (GetGame().IsServer() && IsChamberEmpty(0))
        {
            if (PushCartridgeToChamber(0, 0.0, "BDE_RPG7_Shot_PG7"))
            {
                SetCharged(true);
                RandomizeFSMState();
                BDEUpdateVisuals();
                Synchronize();
                SetSynchDirty();
            }
        }
    }
}

class BDE_Ammo_OG7 extends Ammo_40mm_Explosive
{
}

class BDE_Ammo_PG7 extends BDE_Ammo_OG7
{
}

class BDE_Ammo_PG7R extends BDE_Ammo_OG7
{
}

modded class ModItemRegisterCallbacks
{
    override void RegisterFireArms(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
    {
        super.RegisterFireArms(pType, pBehavior);

        // Match the working launcher hold used by DayZ's IZH-18 hand profile.
        // Parser-sensitive: keep AddItemInHandsProfileIK on one physical source line.
        pType.AddItemInHandsProfileIK("BDE_RPG7", "BDE_RPG7/Animations/player_main_rpg.asi", pBehavior, "dz/anims/anm/player/ik/weapons/izh18.anm", "dz/anims/anm/player/reloads/IZH18/w_izh18_states.anm");
    }

    override void RegisterOneHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
    {
        super.RegisterOneHanded(pType, pBehavior);

        pType.AddItemInHandsProfileIK("RPG7_Bipod", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/attachments/support/bipod_atlas.anm");
        pType.AddItemInHandsProfileIK("RPG7_Optic", "BDE_RPG7/Animations/Hands/pgo7v.asi", pBehavior, "BDE_RPG7/Animations/Hands/pgo7v.anm");
        pType.AddItemInHandsProfileIK("BDE_Ammo_OG7", "BDE_RPG7/Animations/Hands/rocket.asi", pBehavior, "BDE_RPG7/Animations/Hands/rocket_og7.anm");
        pType.AddItemInHandsProfileIK("BDE_Ammo_PG7", "BDE_RPG7/Animations/Hands/rocket.asi", pBehavior, "BDE_RPG7/Animations/Hands/rocket_pg7.anm");
        pType.AddItemInHandsProfileIK("BDE_Ammo_PG7R", "BDE_RPG7/Animations/Hands/rocket.asi", pBehavior, "BDE_RPG7/Animations/Hands/rocket_pg7r.anm");
    }

    override void CustomBoneRemapping(DayZPlayerType pType)
    {
        super.CustomBoneRemapping(pType);

        array<string> rpg7BoneRemap =
        {
            "release", "Weapon_Bone_02",
            "barrel", "Weapon_Bone_01",
            "trigger", "Weapon_Trigger",
            "ejector", "Weapon_Bone_03",
            "bullet", "Weapon_Bullet"
        };
        pType.AddItemBoneRemap("BDE_RPG7", rpg7BoneRemap);
    }
}
