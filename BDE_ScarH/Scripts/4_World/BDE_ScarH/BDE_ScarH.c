modded class SCARH_Base
{
    protected int BDE_ScarH_GetSimpleSelectionIndex(string selectionName)
    {
        TStringArray selections = new TStringArray;
        ConfigGetTextArray("simpleHiddenSelections", selections);
        return selections.Find(selectionName);
    }

    protected void BDE_ScarH_UpdateRailCovers()
    {
        if (IsSetForDeletion())
            return;

        int lowerIndex = BDE_ScarH_GetSimpleSelectionIndex("lower_railcover");
        if (lowerIndex >= 0)
        {
            bool showLower = FindAttachmentBySlotName("weaponBipod") == null;
            SetSimpleHiddenSelectionState(lowerIndex, showLower);
        }

        int leftIndex = BDE_ScarH_GetSimpleSelectionIndex("left_railcover");
        if (leftIndex >= 0)
            SetSimpleHiddenSelectionState(leftIndex, FindAttachmentBySlotName("BDE_SideRail") == null);

        int rightIndex = BDE_ScarH_GetSimpleSelectionIndex("right_railcover");
        if (rightIndex >= 0)
        {
            bool showRight = FindAttachmentBySlotName("weaponFlashlight") == null;
            SetSimpleHiddenSelectionState(rightIndex, showRight);
        }
    }

    protected void BDE_ScarH_QueueRailCoverRefresh()
    {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_ScarH_UpdateRailCovers, 1, false);
    }

    override void EEInit()
    {
        super.EEInit();
        BDE_ScarH_QueueRailCoverRefresh();
    }

    override void AfterStoreLoad()
    {
        super.AfterStoreLoad();
        BDE_ScarH_QueueRailCoverRefresh();
    }

    override void EEItemAttached(EntityAI item, string slot_name)
    {
        super.EEItemAttached(item, slot_name);

        if (slot_name == "weaponBipod" || slot_name == "weaponFlashlight" || slot_name == "BDE_SideRail")
            BDE_ScarH_QueueRailCoverRefresh();
    }

    override void EEItemDetached(EntityAI item, string slot_name)
    {
        super.EEItemDetached(item, slot_name);

        if (slot_name == "weaponBipod" || slot_name == "weaponFlashlight" || slot_name == "BDE_SideRail")
            BDE_ScarH_QueueRailCoverRefresh();
    }
};
