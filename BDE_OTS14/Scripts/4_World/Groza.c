class BDE_OTS14_Groza_Base : RifleBoltFree_Base
{
    bool BDE_OTS14_HasUSL()
    {
        return GetGame().ConfigIsExisting("CfgPatches BDE_UnderSlungLaunchers") && GetGame().ConfigIsExisting("CfgWeapons BDE_OTS14_Launcher");
    }

    override bool CanDisplayAttachmentSlot(int slot_id)
    {
        if (InventorySlots.GetSlotName(slot_id) == "BDE_OTS14_Launcher" && !BDE_OTS14_HasUSL())
        {
            return false;
        }

        return super.CanDisplayAttachmentSlot(slot_id);
    }

    override void SetNextWeaponMode(int muzzleIndex)
    {
        if (BDE_OTS14_HasUSL())
        {
            super.SetNextWeaponMode(muzzleIndex);
            return;
        }
        int nextMode = (GetCurrentMode(muzzleIndex) + 1) % 2;
        SetCurrentMode(muzzleIndex, nextMode);
        OnFireModeChange(nextMode);
    }

    override void EEInit()
    {
        super.EEInit();
        BDE_OTS14_UpdateVisuals();
    }

    override void SyncSelectionState(bool has_bullet, bool has_mag)
    {
        EffectBulletHide(0);
        if (has_bullet)
        {
            ShowBullet(0);
        }
        else
        {
            HideBullet(0);
        }
        if (has_mag)
        {
            ShowMagazine();
        }
        else
        {
            HideMagazine();
        }
    }

    override void ForceSyncSelectionState()
    {
        bool hasBullet = IsChamberFull(0) && !IsChamberFiredOut(0);
        bool hasMagazine = GetMagazine(0) != null;
        SyncSelectionState(hasBullet, hasMagazine);
    }

    override RecoilBase SpawnRecoilObject()
    {
        return new VSSRecoil(this);
    }

    override void OnDebugSpawn()
    {
        SpawnAttachedMagazine("Mag_BDE_OTS14_20Rnd");
    }

    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        string slot = InventorySlots.GetSlotName(slotId);
        if (slot == "BDE_OTS14_Foregrip" || slot == "BDE_OTS14_Suppressor" || slot == "BDE_OTS14_Launcher")
        {
            if (slot != "BDE_OTS14_Foregrip" && FindAttachmentBySlotName("BDE_OTS14_Foregrip"))
            {
                return false;
            }
            if (slot != "BDE_OTS14_Suppressor" && FindAttachmentBySlotName("BDE_OTS14_Suppressor"))
            {
                return false;
            }
            if (slot != "BDE_OTS14_Launcher" && FindAttachmentBySlotName("BDE_OTS14_Launcher"))
            {
                return false;
            }
        }

        if (slot == "BDE_OTS14_Launcher" && (!BDE_OTS14_HasUSL() || !attachment || !attachment.IsKindOf("BDE_OTS14_Launcher")))
        {
            return false;
        }

        if (slot == "BDE_OTS14_Sight" && (!attachment || !attachment.IsKindOf("BDE_OTS14_Sight")))
        {
            return false;
        }

        if (slot == "BDE_OTS14_Suppressor" && (!attachment || !attachment.IsKindOf("BDE_OTS14_Suppressor")))
        {
            return false;
        }

        if (slot == "BDE_OTS14_Foregrip" && FindAttachmentBySlotName("BDE_OTS14_Launcher"))
        {
            return false;
        }

        if (slot == "BDE_OTS14_Launcher" && FindAttachmentBySlotName("BDE_OTS14_Foregrip"))
        {
            return false;
        }

        return super.CanReceiveAttachment(attachment, slotId);
    }

    void BDE_OTS14_UpdateVisuals()
    {
        bool launcherAttached = FindAttachmentBySlotName("BDE_OTS14_Launcher") != null;
        bool muzzleHidden = launcherAttached;
        if (FindAttachmentBySlotName("BDE_OTS14_Foregrip") != null)
        {
            muzzleHidden = true;
        }
        if (FindAttachmentBySlotName("BDE_OTS14_Suppressor") != null)
        {
            muzzleHidden = true;
        }
        SetSimpleHiddenSelectionState(0, !launcherAttached);
        SetSimpleHiddenSelectionState(1, !muzzleHidden);
    }

    override void EEItemAttached(EntityAI item, string slot_name)
    {
        super.EEItemAttached(item, slot_name);
        BDE_OTS14_UpdateVisuals();
    }

    override void EEItemDetached(EntityAI item, string slot_name)
    {
        super.EEItemDetached(item, slot_name);
        BDE_OTS14_UpdateVisuals();
    }

    override void OnVariablesSynchronized()
    {
        super.OnVariablesSynchronized();
        BDE_OTS14_UpdateVisuals();
    }
};

class BDE_OTS14_Groza : BDE_OTS14_Groza_Base
{
};

class Mag_BDE_OTS14_20Rnd : MagazineStorage
{
};

class BDE_OTS14_Sight : ItemOptics
{
};

class BDE_OTS14_Foregrip : Inventory_Base
{
};

class BDE_OTS14_Suppressor : SuppressorBase
{
};

modded class ModItemRegisterCallbacks
{
    override void RegisterFireArms(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
    {
        super.RegisterFireArms(pType, pBehavior);
        pType.AddItemInHandsProfileIK("BDE_OTS14_Groza_Base", "BDE_OTS14/Animations/Player/player_main_groza.asi", pBehavior, "dz/anims/anm/player/ik/weapons/famas.anm", "dz/anims/anm/player/reloads/famas/w_famas_states.anm");
    }

    override void RegisterOneHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
    {
        super.RegisterOneHanded(pType, pBehavior);
        pType.AddItemInHandsProfileIK("BDE_OTS14_Sight", "dz/anims/workspaces/player/player_main/props/player_main_1h_scope.asi", pBehavior, "dz/anims/anm/player/ik/attachments/optic/optic_ots14.anm");
        pType.AddItemInHandsProfileIK("BDE_OTS14_Suppressor", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/attachments/muzzle/suppressor_545.anm");
        pType.AddItemInHandsProfileIK("BDE_OTS14_Foregrip", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/attachments/muzzle/suppressor_545.anm");
    }
};
