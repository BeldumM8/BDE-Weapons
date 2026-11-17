#ifdef S_GUNPLAY
modded class PropertyModifiers
{
    override void UpdateModifiers()
    {
        super.UpdateModifiers();

        Weapon_Base weapon = Weapon_Base.Cast(m_OwnerItem);
        if (!BDE_Bipod.BDE_HasDeployedSupport(weapon))
            return;

        recoilControlHandsX = 1.0;
        recoilControlHandsY = 1.0;
        recoilControlMisalignmentX = 1.0;
        recoilControlMisalignmentY = 1.0;
        recoilControlKick = Math.Clamp(1.0 - ((1.0 - recoilControlKick) * 0.5), -1.0, 1.0);
    }
}
#endif
