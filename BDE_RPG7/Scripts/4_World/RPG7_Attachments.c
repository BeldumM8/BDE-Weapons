class RPG7_Bipod extends Inventory_Base
{
    protected bool m_BDEDeployed;
    protected ref Timer m_BDECheckTimer;

    void RPG7_Bipod()
    {
        RegisterNetSyncVariableBool("m_BDEDeployed");
    }

    override void EEInit()
    {
        super.EEInit();

        BDEApplyPose();

        if (!GetGame().IsServer())
            return;

        m_BDECheckTimer = new Timer(CALL_CATEGORY_SYSTEM);
        m_BDECheckTimer.Run(0.2, this, "BDEUpdateDeployment", null, true);

        BDEUpdateDeployment();
    }

    override void EEDelete(EntityAI parent)
    {
        if (m_BDECheckTimer)
            m_BDECheckTimer.Stop();

        super.EEDelete(parent);
    }

    override void OnVariablesSynchronized()
    {
        super.OnVariablesSynchronized();
        BDEApplyPose();
    }

    void BDEUpdateDeployment()
    {
        bool deployed = false;
        Weapon_Base weapon = Weapon_Base.Cast(GetHierarchyParent());

        if (weapon)
        {
            string modelPath;
            GetGame().ConfigGetText("CfgWeapons " + weapon.GetType() + " model", modelPath);

            modelPath.ToLower();
            modelPath.Replace("/", "\\");

            if (modelPath.Contains("bde_rpg7\\models\\rpg7.p3d"))
            {
                PlayerBase player = PlayerBase.Cast(weapon.GetHierarchyRootPlayer());

                if (player)
                    deployed = player.GetHumanInventory().GetEntityInHands() == weapon;
            }
        }

        if (m_BDEDeployed == deployed)
            return;

        m_BDEDeployed = deployed;
        BDEApplyPose();
        SetSynchDirty();
    }

    protected void BDEApplyPose()
    {
        float phase = 0.0;

        if (m_BDEDeployed)
            phase = 1.0;

        SetAnimationPhase("leg_left_deploy", phase);
        SetAnimationPhase("leg_right_deploy", phase);
    }
}

class RPG7_Sights extends Inventory_Base
{
    protected bool m_BDEFrontFolded = true;
    protected bool m_BDERearFolded = true;

    void RPG7_Sights()
    {
        RegisterNetSyncVariableBool("m_BDEFrontFolded");
        RegisterNetSyncVariableBool("m_BDERearFolded");
    }

    override void EEInit()
    {
        super.EEInit();
        BDEApplySightPose();
    }

    override void OnVariablesSynchronized()
    {
        super.OnVariablesSynchronized();
        BDEApplySightPose();
    }

    // Phase 0 = upright, phase 1 = folded.
    // Call on the server; the selected pose is synchronised to clients.
    void BDESetFolded(bool frontFolded, bool rearFolded)
    {
        if (!GetGame().IsServer())
            return;

        if (m_BDEFrontFolded == frontFolded && m_BDERearFolded == rearFolded)
            return;

        m_BDEFrontFolded = frontFolded;
        m_BDERearFolded = rearFolded;

        BDEApplySightPose();
        SetSynchDirty();
    }

    protected void BDEApplySightPose()
    {
        float frontPhase = 0.0;
        float rearPhase = 0.0;

        if (m_BDEFrontFolded)
            frontPhase = 1.0;

        if (m_BDERearFolded)
            rearPhase = 1.0;

        SetAnimationPhase("front_sight_fold", frontPhase);
        SetAnimationPhase("rear_sight_fold", rearPhase);
    }
}

class RPG7_Optic extends ItemOptics
{
    protected ref Timer m_BDEOpticVisualTimer;

    override void EEInit()
    {
        super.EEInit();

        if (!GetGame().IsDedicatedServer())
        {
            m_BDEOpticVisualTimer = new Timer(CALL_CATEGORY_SYSTEM);
            m_BDEOpticVisualTimer.Run(0.05, this, "BDEUpdateOpticVisual", null, true);
            BDEUpdateOpticVisual();
        }
    }

    override void EEDelete(EntityAI parent)
    {
        if (m_BDEOpticVisualTimer)
            m_BDEOpticVisualTimer.Stop();

        super.EEDelete(parent);
    }

    protected void BDEUpdateOpticVisual()
    {
        // Hide the physical PGO-7 body while the camera is actually inside
        // the optic. The third-person/inventory model remains unchanged.
        float phase = 0.0;

        if (IsInOptics())
            phase = 1.0;

        SetAnimationPhase("optic_hide", phase);
    }
}
