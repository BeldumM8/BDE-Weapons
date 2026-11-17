modded class RecoilBase
{
    override vector GetRecoilModifier(Weapon_Base weapon)
    {
        vector modifier = super.GetRecoilModifier(weapon);
        if (BDE_Bipod.BDE_HasDeployedSupport(weapon))
            modifier = modifier * 0.03;
        return modifier;
    }
};

modded class DayZPlayerImplementAiming
{
    override protected float CalculateWeight(int stance_index, float current_stamina, float camera_sway_modifier, bool holding_breath)
    {
        float weight = super.CalculateWeight(stance_index, current_stamina, camera_sway_modifier, holding_breath);
        Weapon_Base weapon = Weapon_Base.Cast(m_PlayerPb.GetHumanInventory().GetEntityInHands());
        if (BDE_Bipod.BDE_HasDeployedSupport(weapon))
            weight = weight * 0.03;
        return weight;
    }
};
