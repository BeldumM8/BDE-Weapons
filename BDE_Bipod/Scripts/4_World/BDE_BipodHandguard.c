modded class Weapon_Base
{
    protected string BDE_Bipod_RequiredHandguardSlot()
    {
        if (IsKindOf("M4A1"))
            return "WeaponHandguardM4";
        if (IsKindOf("AKM") || IsKindOf("AK101") || IsKindOf("AK74"))
            return "WeaponHandguardAK";
        return "";
    }

    protected bool BDE_Bipod_HasRequiredHandguard()
    {
        string slot = BDE_Bipod_RequiredHandguardSlot();
        if (slot == "")
            return true;

        EntityAI handguard = FindAttachmentBySlotName(slot);
        if (!handguard)
            return false;
        if (slot == "WeaponHandguardM4")
            return handguard.IsKindOf("M4_RISHndgrd");
        return handguard.IsKindOf("AK_RailHndgrd");
    }

    override bool CanDisplayAttachmentSlot(int slot_id)
    {
        if (slot_id == InventorySlots.GetSlotIdFromString("weaponBipod"))
        {
            // The slot is shared with underslung weapons. An installed item
            // must remain visible even if it does not need a rail handguard.
            if (!FindAttachmentBySlotName("weaponBipod") && !BDE_Bipod_HasRequiredHandguard())
                return false;
        }
        return super.CanDisplayAttachmentSlot(slot_id);
    }

    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        // The USL mod validates launcher handguards itself. Use a config
        // inheritance check so the bipod mod does not depend on USL scripts.
        bool underslung = attachment && attachment.IsKindOf("BDE_UnderSlungLauncher_Base");
        if (!underslung && slotId == InventorySlots.GetSlotIdFromString("weaponBipod") && !BDE_Bipod_HasRequiredHandguard())
            return false;
        return super.CanReceiveAttachment(attachment, slotId);
    }

    override bool CanReleaseAttachment(EntityAI attachment)
    {
        string slot = BDE_Bipod_RequiredHandguardSlot();
        if (slot != "" && attachment && attachment == FindAttachmentBySlotName(slot) && FindAttachmentBySlotName("weaponBipod"))
            return false;
        return super.CanReleaseAttachment(attachment);
    }
};
