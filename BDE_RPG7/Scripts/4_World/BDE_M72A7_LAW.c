class BDELAWMeasuredMotion
{
    static float OpenTube(float frame)
    {
        if (frame <= 63.0)
            return 0.00000000;
        if (frame <= 64.0)
            return 0.00000000 + (frame - 63.0) * 0.06478588;
        if (frame <= 65.0)
            return 0.06478588 + (frame - 64.0) * 0.20230700;
        if (frame <= 66.0)
            return 0.26709289 + (frame - 65.0) * 0.27466211;
        if (frame <= 67.0)
            return 0.54175499 + (frame - 66.0) * 0.23011071;
        if (frame <= 68.0)
            return 0.77186570 + (frame - 67.0) * 0.14755896;
        if (frame <= 69.0)
            return 0.91942466 + (frame - 68.0) * 0.08057534;
        return 1.00000000;
    }
    static float CloseTube(float frame)
    {
        if (frame <= 28.0)
            return 1.00000000;
        if (frame <= 29.0)
            return 1.00000000 + (frame - 28.0) * -0.00166568;
        if (frame <= 30.0)
            return 0.99833432 + (frame - 29.0) * -0.01966142;
        if (frame <= 31.0)
            return 0.97867290 + (frame - 30.0) * -0.13237496;
        if (frame <= 32.0)
            return 0.84629793 + (frame - 31.0) * -0.20031193;
        if (frame <= 33.0)
            return 0.64598600 + (frame - 32.0) * -0.10993584;
        if (frame <= 34.0)
            return 0.53605016 + (frame - 33.0) * -0.06637339;
        if (frame <= 35.0)
            return 0.46967677 + (frame - 34.0) * -0.05197210;
        if (frame <= 36.0)
            return 0.41770467 + (frame - 35.0) * -0.05285460;
        if (frame <= 37.0)
            return 0.36485007 + (frame - 36.0) * -0.00607369;
        if (frame <= 38.0)
            return 0.35877638 + (frame - 37.0) * 0.00000000;
        if (frame <= 39.0)
            return 0.35877638 + (frame - 38.0) * 0.00000000;
        if (frame <= 40.0)
            return 0.35877638 + (frame - 39.0) * 0.00000000;
        if (frame <= 41.0)
            return 0.35877638 + (frame - 40.0) * 0.00000000;
        if (frame <= 42.0)
            return 0.35877638 + (frame - 41.0) * 0.00000000;
        if (frame <= 43.0)
            return 0.35877638 + (frame - 42.0) * 0.00000000;
        if (frame <= 44.0)
            return 0.35877638 + (frame - 43.0) * 0.00153859;
        if (frame <= 45.0)
            return 0.36031497 + (frame - 44.0) * -0.00153859;
        if (frame <= 46.0)
            return 0.35877638 + (frame - 45.0) * 0.00000000;
        if (frame <= 47.0)
            return 0.35877638 + (frame - 46.0) * 0.00000000;
        if (frame <= 48.0)
            return 0.35877638 + (frame - 47.0) * 0.00000000;
        if (frame <= 49.0)
            return 0.35877638 + (frame - 48.0) * 0.00000000;
        if (frame <= 50.0)
            return 0.35877638 + (frame - 49.0) * 0.00000000;
        if (frame <= 51.0)
            return 0.35877638 + (frame - 50.0) * 0.00000000;
        if (frame <= 52.0)
            return 0.35877638 + (frame - 51.0) * 0.00000000;
        if (frame <= 53.0)
            return 0.35877638 + (frame - 52.0) * 0.00000000;
        if (frame <= 54.0)
            return 0.35877638 + (frame - 53.0) * 0.00000000;
        if (frame <= 55.0)
            return 0.35877638 + (frame - 54.0) * 0.00000000;
        if (frame <= 56.0)
            return 0.35877638 + (frame - 55.0) * 0.00000000;
        if (frame <= 57.0)
            return 0.35877638 + (frame - 56.0) * 0.00000000;
        if (frame <= 58.0)
            return 0.35877638 + (frame - 57.0) * 0.00000000;
        if (frame <= 59.0)
            return 0.35877638 + (frame - 58.0) * 0.00000000;
        if (frame <= 60.0)
            return 0.35877638 + (frame - 59.0) * 0.00000000;
        if (frame <= 61.0)
            return 0.35877638 + (frame - 60.0) * 0.00000000;
        if (frame <= 62.0)
            return 0.35877638 + (frame - 61.0) * 0.00000000;
        if (frame <= 63.0)
            return 0.35877638 + (frame - 62.0) * 0.00000000;
        if (frame <= 64.0)
            return 0.35877638 + (frame - 63.0) * 0.00000000;
        if (frame <= 65.0)
            return 0.35877638 + (frame - 64.0) * 0.00000000;
        if (frame <= 66.0)
            return 0.35877638 + (frame - 65.0) * 0.00000000;
        if (frame <= 67.0)
            return 0.35877638 + (frame - 66.0) * 0.00000000;
        if (frame <= 68.0)
            return 0.35877638 + (frame - 67.0) * 0.00000000;
        if (frame <= 69.0)
            return 0.35877638 + (frame - 68.0) * 0.00000000;
        if (frame <= 70.0)
            return 0.35877638 + (frame - 69.0) * 0.00000000;
        if (frame <= 71.0)
            return 0.35877638 + (frame - 70.0) * 0.00000000;
        if (frame <= 72.0)
            return 0.35877638 + (frame - 71.0) * 0.00000000;
        if (frame <= 73.0)
            return 0.35877638 + (frame - 72.0) * 0.00000000;
        if (frame <= 74.0)
            return 0.35877638 + (frame - 73.0) * 0.00000000;
        if (frame <= 75.0)
            return 0.35877638 + (frame - 74.0) * 0.00000000;
        if (frame <= 76.0)
            return 0.35877638 + (frame - 75.0) * 0.00000000;
        if (frame <= 77.0)
            return 0.35877638 + (frame - 76.0) * 0.00000000;
        if (frame <= 78.0)
            return 0.35877638 + (frame - 77.0) * 0.00000000;
        if (frame <= 79.0)
            return 0.35877638 + (frame - 78.0) * 0.00000000;
        if (frame <= 80.0)
            return 0.35877638 + (frame - 79.0) * 0.00000000;
        if (frame <= 81.0)
            return 0.35877638 + (frame - 80.0) * 0.00000000;
        if (frame <= 82.0)
            return 0.35877638 + (frame - 81.0) * 0.00000000;
        if (frame <= 83.0)
            return 0.35877638 + (frame - 82.0) * 0.00000000;
        if (frame <= 84.0)
            return 0.35877638 + (frame - 83.0) * 0.00000000;
        if (frame <= 85.0)
            return 0.35877638 + (frame - 84.0) * 0.00000000;
        if (frame <= 86.0)
            return 0.35877638 + (frame - 85.0) * 0.00000000;
        if (frame <= 87.0)
            return 0.35877638 + (frame - 86.0) * 0.00000000;
        if (frame <= 88.0)
            return 0.35877638 + (frame - 87.0) * -0.03746364;
        if (frame <= 89.0)
            return 0.32131274 + (frame - 88.0) * -0.04922452;
        if (frame <= 90.0)
            return 0.27208822 + (frame - 89.0) * -0.04575112;
        if (frame <= 91.0)
            return 0.22633711 + (frame - 90.0) * -0.04829492;
        if (frame <= 92.0)
            return 0.17804218 + (frame - 91.0) * -0.05369468;
        if (frame <= 93.0)
            return 0.12434750 + (frame - 92.0) * -0.05495425;
        if (frame <= 94.0)
            return 0.06939325 + (frame - 93.0) * -0.04563398;
        if (frame <= 95.0)
            return 0.02375927 + (frame - 94.0) * -0.02375927;
        return 0.00000000;
    }
}

class BDE_LAW_Empty : BDE_RPG7_Empty
{
    override bool IsRepairEnabled()
    {
        return false;
    }
}

class BDE_LAW_Loaded : BDE_RPG7_Loaded
{
    override bool IsRepairEnabled()
    {
        return false;
    }
}

class BDE_LAW_CanFire : WeaponGuardBase
{
    protected BDE_M72A7_LAW m_Launcher;

    void BDE_LAW_CanFire(BDE_M72A7_LAW launcher)
    {
        m_Launcher = launcher;
    }

    override bool GuardCondition(WeaponEventBase e)
    {
        return m_Launcher && m_Launcher.CanFire();
    }
}

class BDE_LAW_Operate : WeaponStartAction
{
    protected bool m_Aborted;

    override bool IsWaitingForActionFinish()
    {
        return true;
    }

    override void OnEntry(WeaponEventBase e)
    {
        m_Aborted = false;
        BDE_M72A7_LAW launcher = BDE_M72A7_LAW.Cast(m_weapon);
        m_action = WeaponActions.MECHANISM;
        m_actionType = WeaponActionMechanismTypes.MECHANISM_OPENED;
        if (launcher.BDEIsUnfolded())
            m_actionType = WeaponActionMechanismTypes.MECHANISM_CLOSED;
        launcher.BDEBeginOperation();
        super.OnEntry(e);
    }

    override void OnUpdate(float dt)
    {
        super.OnUpdate(dt);
        BDE_M72A7_LAW.Cast(m_weapon).BDEUpdateVisuals();
    }

    override void OnAbort(WeaponEventBase e)
    {
        m_Aborted = true;
        BDE_M72A7_LAW.Cast(m_weapon).BDEEndOperation(false);
        super.OnAbort(e);
    }

    override void OnExit(WeaponEventBase e)
    {
        super.OnExit(e);
        if (!m_Aborted)
            BDE_M72A7_LAW.Cast(m_weapon).BDEEndOperation(true);
    }
}

class BDE_LAW_SwapLambda : TurnItemIntoItemLambda
{
    protected bool m_Spent;
    protected bool m_Loaded;
    protected float m_RoundDamage;

    void BDE_LAW_SwapLambda(EntityAI old_item, string new_item_type, PlayerBase player, bool spent, bool loaded, float roundDamage)
    {
        m_Spent = spent;
        m_Loaded = loaded;
        m_RoundDamage = roundDamage;
    }

    override void OnAbort()
    {
        super.OnAbort();
        BDE_M72A7_LAW launcher = BDE_M72A7_LAW.Cast(m_OldItem);
        if (launcher)
            launcher.BDESwapFailed();
    }

    override void OnSuccess(EntityAI new_item)
    {
        super.OnSuccess(new_item);
        BDE_M72A7_LAW launcher = BDE_M72A7_LAW.Cast(new_item);
        if (launcher)
            launcher.BDEFinishSwap(m_Spent, m_Loaded, m_RoundDamage);
    }
}

class BDE_M72A7_LAW : BDE_RPG7
{
    protected bool m_LAWInitialized;
    protected bool m_LAWSpent;
    protected bool m_LAWOperating;
    protected bool m_LAWSwapPending;
    protected int m_LAWOperationStarted;

    void BDE_M72A7_LAW()
    {
        RegisterNetSyncVariableBool("m_LAWSpent");
    }

    bool BDEIsUnfolded()
    {
        return false;
    }

    override void InitStateMachine()
    {
        m_abilities.Insert(new AbilityRecord(WeaponActions.MECHANISM, WeaponActionMechanismTypes.MECHANISM_OPENED));
        m_abilities.Insert(new AbilityRecord(WeaponActions.MECHANISM, WeaponActionMechanismTypes.MECHANISM_CLOSED));
        m_abilities.Insert(new AbilityRecord(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_NORMAL));
        m_abilities.Insert(new AbilityRecord(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_COCKED));

        WeaponStableState empty = new BDE_LAW_Empty(this, null, BDE_RPG7_AnimState.DEFAULT);
        WeaponStableState loaded = new BDE_LAW_Loaded(this, null, BDE_RPG7_AnimState.DEFAULT);
        BDE_LAW_Operate operate = new BDE_LAW_Operate(this);
        WeaponFire fire = new WeaponFire(this, null, WeaponActions.FIRE, WeaponActionFireTypes.FIRE_NORMAL);
        WeaponDryFire dryFire = new WeaponDryFire(this, null, WeaponActions.FIRE, WeaponActionFireTypes.FIRE_COCKED);
        WeaponEventBase mechanism = new WeaponEventMechanism;
        WeaponEventBase trigger = new WeaponEventTrigger;
        WeaponEventBase finished = new WeaponEventHumanCommandActionFinished;
        WeaponEventBase aborted = new WeaponEventHumanCommandActionAborted;
        WeaponEventBase timeout = new WeaponEventDryFireTimeout;

        // No loading, cartridge transfer or ejection transitions exist.
        m_fsm = new WeaponFSM();
        m_fsm.AddTransition(new WeaponTransition(loaded, mechanism, operate));
        m_fsm.AddTransition(new WeaponTransition(operate, finished, loaded));
        m_fsm.AddTransition(new WeaponTransition(operate, aborted, loaded));
        m_fsm.AddTransition(new WeaponTransition(loaded, trigger, fire, null, new BDE_LAW_CanFire(this)));
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

    override bool CanFire()
    {
        return BDEIsUnfolded() && !m_LAWSpent && !m_LAWSwapPending && super.CanFire();
    }

    override bool CanChamberBullet(int muzzleIndex, Magazine mag)
    {
        return false;
    }

    override bool CanEjectBullet()
    {
        // The vanilla manipulation input invokes our fold/unfold state.
        // That state never ejects or transfers a cartridge.
        PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());
        if (!player || !player.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_ERECT))
            return false;
        return !m_LAWSpent && !m_LAWSwapPending && IsChamberFull(0) && !IsRuined();
    }

    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        return attachment && attachment.GetType() == "BDE_LAW_Parts" && slotId == InventorySlots.GetSlotIdFromString("BDE_LAW_Parts");
    }

    override void BDEEnsureSights()
    {
        if (GetGame().IsServer() && !FindAttachmentBySlotName("BDE_LAW_Parts"))
            GetInventory().CreateAttachment("BDE_LAW_Parts");
        BDEUpdateVisuals();
    }

    override void EEInit()
    {
        super.EEInit();
        if (GetGame().IsServer())
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDEInitializeLAW, 300, false);
    }

    override void EEDelete(EntityAI parent)
    {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDEInitializeLAW);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDESwapLAW);
        super.EEDelete(parent);
    }

    void BDEInitializeLAW()
    {
        if (m_LAWInitialized)
            return;
        m_LAWInitialized = true;
        m_LAWSpent = false;
        SetHealth01("", "Health", 1.0);
        if (IsChamberEmpty(0))
            PushCartridgeToChamber(0, 0.0, "BDE_RPG7_Shot_PG7");
        RandomizeFSMState();
        Synchronize();
        SetSynchDirty();
        if (BDEIsUnfolded())
            BDESwapLAW();
    }

    override void OnDebugSpawn()
    {
        BDEInitializeLAW();
    }

    override void OnStoreSave(ParamsWriteContext ctx)
    {
        super.OnStoreSave(ctx);
        ctx.Write(m_LAWInitialized);
        ctx.Write(m_LAWSpent);
    }

    override bool OnStoreLoad(ParamsReadContext ctx, int version)
    {
        if (!super.OnStoreLoad(ctx, version))
            return false;
        if (!ctx.Read(m_LAWInitialized))
            return false;
        if (!ctx.Read(m_LAWSpent))
            return false;
        // Loading a saved item must never run fresh-spawn initialization.
        m_LAWInitialized = true;
        return true;
    }

    void BDEBeginOperation()
    {
        m_LAWOperating = true;
        m_LAWOperationStarted = GetGame().GetTime();
    }

    void BDEEndOperation(bool complete)
    {
        m_LAWOperating = false;
        if (complete && GetGame().IsServer())
        {
            m_LAWSwapPending = true;
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDESwapLAW, 1, false);
        }
        BDEUpdateVisuals();
    }

    void BDESwapFailed()
    {
        m_LAWSwapPending = false;
        BDEUpdateVisuals();
    }

    bool BDEIsSwapping()
    {
        return m_LAWSwapPending;
    }

    void BDESwapLAW()
    {
        if (!GetGame().IsServer())
            return;
        PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());
        string replacement = "BDE_M72A7_LAW_Unfolded";
        if (BDEIsUnfolded())
            replacement = "BDE_M72A7_LAW";
        float damage;
        string ammo;
        bool loaded = IsChamberFull(0) && !IsChamberFiredOut(0);
        if (loaded)
            GetCartridgeInfo(0, damage, ammo);
        m_LAWSwapPending = true;
        BDE_LAW_SwapLambda lambda = new BDE_LAW_SwapLambda(this, replacement, player, m_LAWSpent, loaded, damage);
        lambda.SetTransferParams(true, true, true);
        GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, lambda);
    }

    void BDEFinishSwap(bool spent, bool loaded, float roundDamage)
    {
        m_LAWInitialized = true;
        m_LAWSpent = spent;
        BDEEnsureSights();
        if (!IsChamberEmpty(0))
        {
            float oldDamage;
            string oldAmmo;
            PopCartridgeFromChamber(0, oldDamage, oldAmmo);
        }
        if (loaded && !spent)
            PushCartridgeToChamber(0, roundDamage, "BDE_RPG7_Shot_PG7");
        if (spent)
            SetHealth01("", "Health", 0.0);
        RandomizeFSMState();
        Synchronize();
        SetSynchDirty();
        BDEUpdateVisuals();
    }

    override void BDEUpdateVisuals()
    {
        // Pose modes: 0 folded, 1 unfolded, 2 unfolding, 3 folding.
        int poseMode;
        float frame;
        if (BDEIsUnfolded())
            poseMode = 1;
        if (m_LAWOperating)
        {
            poseMode = 2;
            if (BDEIsUnfolded())
                poseMode = 3;
            frame = (GetGame().GetTime() - m_LAWOperationStarted) * 0.03;
        }
        else if (m_LAWSwapPending)
        {
            poseMode = 1 - poseMode;
        }
        BDE_LAW_Parts parts = BDE_LAW_Parts.Cast(FindAttachmentBySlotName("BDE_LAW_Parts"));
        if (parts && (GetGame().IsServer() || m_LAWOperating))
            parts.BDEApplyLAW(poseMode, frame, m_LAWSpent);
    }

    override protected string BDEGetFlightClass(string ammoType)
    {
        return "BDE_LAW_Flight";
    }

    override void EEFired(int muzzleType, int mode, string ammoType)
    {
        super.EEFired(muzzleType, mode, ammoType);
        if (GetGame().IsServer())
        {
            m_LAWSpent = true;
            SetHealth01("", "Health", 0.0);
            SetSynchDirty();
        }
        BDEUpdateVisuals();
    }
}

class BDE_M72A7_LAW_Unfolded : BDE_M72A7_LAW
{
    override bool BDEIsUnfolded()
    {
        return true;
    }
}

class BDE_LAW_Flight : BDE_RPG7_Flight_PG7
{
    override protected void BDEUpdateFlightVisuals()
    {
        for (int i = 1; i <= 6; i++)
            SetAnimationPhaseNow("fin_" + i.ToString() + "_deploy", m_BDEFinPhase);
    }
}

modded class ModItemRegisterCallbacks
{
    override void RegisterFireArms(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
    {
        super.RegisterFireArms(pType, pBehavior);
        // Both LAW variants use the RPG firearm grip; the LAW ASI retains its fold actions.
        pType.AddItemInHandsProfileIK("BDE_M72A7_LAW", "BDE_RPG7/Animations/player_main_law.asi", pBehavior, "dz/anims/anm/player/ik/weapons/izh18.anm", "dz/anims/anm/player/reloads/IZH18/w_izh18_states.anm");
        pType.AddItemInHandsProfileIK("BDE_M72A7_LAW_Unfolded", "BDE_RPG7/Animations/player_main_law.asi", pBehavior, "dz/anims/anm/player/ik/weapons/izh18.anm", "dz/anims/anm/player/reloads/IZH18/w_izh18_states.anm");
    }
}

// Moving launcher geometry belongs to this proxy item, never Weapon_Base.
class BDE_LAW_Parts : Inventory_Base
{
    protected int m_LAWPoseMode;
    protected float m_LAWFrame;
    protected bool m_LAWEmpty;

    void BDE_LAW_Parts()
    {
        RegisterNetSyncVariableInt("m_LAWPoseMode", 0, 3);
        RegisterNetSyncVariableFloat("m_LAWFrame", 0.0, 181.0, 2);
        RegisterNetSyncVariableBool("m_LAWEmpty");
    }

    override void OnVariablesSynchronized()
    {
        super.OnVariablesSynchronized();
        BDEApplyLAW(m_LAWPoseMode, m_LAWFrame, m_LAWEmpty);
    }

    override bool CanDetachAttachment(EntityAI parent)
    {
        BDE_M72A7_LAW launcher = BDE_M72A7_LAW.Cast(parent);
        return launcher && launcher.BDEIsSwapping();
    }

    protected float BDEFramePhase(float frame, float first, float last)
    {
        return Math.Clamp((frame - first) / (last - first), 0.0, 1.0);
    }

    void BDEApplyLAW(int poseMode, float frame, bool spent)
    {
        frame = Math.Clamp(frame, 0.0, 181.0);
        if (GetGame().IsServer() && (poseMode != m_LAWPoseMode || Math.AbsFloat(frame - m_LAWFrame) > 0.02 || spent != m_LAWEmpty))
        {
            m_LAWPoseMode = poseMode;
            m_LAWFrame = frame;
            m_LAWEmpty = spent;
            SetSynchDirty();
        }

        float cap;
        float cover;
        float tube;
        float front;
        float rear;
        float safety;
        if (poseMode == 1)
        {
            cap = 1.0;
            cover = 1.0;
            tube = 1.0;
            front = 1.0;
            rear = 1.0;
            safety = 1.0;
        }
        else if (poseMode == 2)
        {
            cover = 1.0;
            // Hand releases at 42; the cap continues swinging to frame 50.
            cap = BDEFramePhase(frame, 32.0, 50.0);
            tube = BDELAWMeasuredMotion.OpenTube(frame);
            front = BDEFramePhase(frame, 65.0, 69.0);
            rear = front;
            safety = BDEFramePhase(frame, 106.0, 112.0);
        }
        else if (poseMode == 3)
        {
            safety = 1.0 - BDEFramePhase(frame, 8.0, 14.0);
            tube = BDELAWMeasuredMotion.CloseTube(frame);
            front = 1.0 - BDEFramePhase(frame, 56.0, 60.0);
            rear = 1.0 - BDEFramePhase(frame, 79.0, 83.0);
            cap = 1.0 - BDEFramePhase(frame, 131.0, 144.0);
            cover = 1.0;
            if (frame >= 144.0)
                cover = 0.0;
        }
        SetAnimationPhaseNow("tube_cap_deploy", cap);
        SetAnimationPhaseNow("sight_cover_hide", cover);
        SetAnimationPhaseNow("tube_extend", tube);
        SetAnimationPhaseNow("front_sight_deploy", front);
        SetAnimationPhaseNow("rear_sight_deploy", rear);
        SetAnimationPhaseNow("safety_slide", safety);
        float hideRocket;
        if (spent)
            hideRocket = 1.0;
        SetAnimationPhaseNow("rocket_hide", hideRocket);
    }
}
