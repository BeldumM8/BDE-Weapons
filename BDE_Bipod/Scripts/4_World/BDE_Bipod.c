class BDE_Bipod extends Inventory_Base
{
    protected bool m_BDE_Deployed;
    protected bool m_BDE_VisualDeployed;

    void BDE_Bipod()
    {
        RegisterNetSyncVariableBool("m_BDE_Deployed");
    }

    override void EEInit()
    {
        super.EEInit();
        BDE_ApplyDeployment(false, true);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_RefreshPolling, 1, false);
    }

    override void AfterStoreLoad()
    {
        super.AfterStoreLoad();
        BDE_RefreshPolling();
    }

    override void OnWasAttached(EntityAI parent, int slot_id)
    {
        super.OnWasAttached(parent, slot_id);
        BDE_RefreshPolling();
    }

    override void OnWasDetached(EntityAI parent, int slot_id)
    {
        super.OnWasDetached(parent, slot_id);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_PollDeployment);
        BDE_SetServerDeployment(false);
        BDE_ApplyDeployment(false);
    }

    override void EEDelete(EntityAI parent)
    {
        if (GetGame())
        {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_RefreshPolling);
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_PollDeployment);
#ifdef S_GUNPLAY
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_sGunPlay_RefreshHostModifiers);
#endif
        }
        super.EEDelete(parent);
    }

    override void OnVariablesSynchronized()
    {
        super.OnVariablesSynchronized();
        BDE_PollDeployment();
    }

    protected void BDE_RefreshPolling()
    {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_PollDeployment);
        if (Weapon_Base.Cast(GetHierarchyParent()))
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_PollDeployment, 100, true);
        BDE_PollDeployment();
    }

    bool BDE_ShouldDeploy()
    {
        if (IsRuined())
            return false;
        Weapon_Base weapon = Weapon_Base.Cast(GetHierarchyParent());
        if (!weapon)
            return false;
        PlayerBase player = PlayerBase.Cast(weapon.GetHierarchyRootPlayer());
        if (!player || !player.IsAlive() || player.IsUnconscious())
            return false;
        if (player.GetHumanInventory().GetEntityInHands() != weapon)
            return false;
        if (!player.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_PRONE | DayZPlayerConstants.STANCEMASK_RAISEDPRONE))
            return false;
        HumanCommandMove movement = player.GetCommand_Move();
        return movement && !movement.IsOnBack() && !movement.IsInRoll();
    }

    protected void BDE_SetServerDeployment(bool deploy)
    {
        if (GetGame().IsServer() && m_BDE_Deployed != deploy)
        {
            m_BDE_Deployed = deploy;
            SetSynchDirty();
        }
    }

    protected void BDE_PollDeployment()
    {
        if (IsSetForDeletion())
            return;
        bool deploy = m_BDE_Deployed;
        PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());

        if (GetGame().IsServer() || (player && player == GetGame().GetPlayer()))
        {
            deploy = BDE_ShouldDeploy();
            BDE_SetServerDeployment(deploy);
        }
        if (!Weapon_Base.Cast(GetHierarchyParent()) || IsRuined())
            deploy = false;
        BDE_ApplyDeployment(deploy);
    }

    protected void BDE_ApplyDeployment(bool deploy, bool force = false)
    {
        if (!force && m_BDE_VisualDeployed == deploy)
            return;
        m_BDE_VisualDeployed = deploy;
        float phase = 0;
        if (deploy)
            phase = 1;
        SetAnimationPhase("left_leg_deploy", phase);
        SetAnimationPhase("right_leg_deploy", phase);
        SetAnimationPhase("left_leg_extend", phase);
        SetAnimationPhase("right_leg_extend", phase);
#ifdef S_GUNPLAY
        BDE_sGunPlay_RefreshHostModifiers();
        if (deploy && GetGame())
        {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_sGunPlay_RefreshHostModifiers, 400, false);
        }
#endif
    }

#ifdef S_GUNPLAY
    protected void BDE_sGunPlay_RefreshHostModifiers()
    {
        Weapon_Base weapon = Weapon_Base.Cast(GetHierarchyParent());
        if (!weapon)
        {
            return;
        }

        PropertyModifiers modifiers = weapon.GetPropertyModifierObject();
        if (modifiers)
        {
            modifiers.UpdateModifiers();
        }
    }
#endif

    bool BDE_IsSupportingWeapon()
    {
        return BDE_ShouldDeploy() && GetAnimationPhase("left_leg_deploy") >= 0.98 && GetAnimationPhase("right_leg_deploy") >= 0.98 && GetAnimationPhase("left_leg_extend") >= 0.98 && GetAnimationPhase("right_leg_extend") >= 0.98;
    }

    static bool BDE_HasDeployedSupport(Weapon_Base weapon)
    {
        if (!weapon)
            return false;
        BDE_Bipod bipod = BDE_Bipod.Cast(weapon.FindAttachmentBySlotName("weaponBipod"));
        return bipod && bipod.BDE_IsSupportingWeapon();
    }
};

modded class ModItemRegisterCallbacks
{
    override void RegisterOneHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
    {
        super.RegisterOneHanded(pType, pBehavior);
        pType.AddItemInHandsProfileIK("BDE_Bipod", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/attachments/support/bipod_atlas.anm");
    }
};
