class CfgPatches
{
    class BDE_Bipod
    {
        units[] = {"BDE_Bipod"};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data", "DZ_Weapons_Supports", "DZ_Weapons_Firearms_M4", "DZ_Weapons_Firearms_AKM", "DZ_Weapons_Firearms_AK101", "DZ_Weapons_Firearms_AK74"};
    };
};

class CfgMods
{
    class BDE_Bipod
    {
        dir = "BDE_Bipod";
        name = "BDE Bipod";
        type = "mod";
        dependencies[] = {"World"};
        class defs
        {
            class worldScriptModule
            {
                value = "";
                files[] = {"BDE_Bipod/Scripts/4_World"};
            };
        };
    };
};

class CfgWeapons
{
    class M4A1_Base;
    class M4A1 : M4A1_Base
    {
        attachments[] = {"weaponButtstockM4", "WeaponHandguardM4", "weaponWrap", "weaponOptics", "weaponFlashlight", "weaponMuzzleM4", "weaponBayonet", "weaponBipod"};
    };

    class AKM_Base;
    class AKM : AKM_Base
    {
        attachments[] = {"weaponButtstockAK", "WeaponHandguardAK", "weaponWrap", "weaponOpticsAK", "weaponFlashlight", "weaponMuzzleAK", "weaponBayonetAK", "weaponBipod"};
    };

    class AK101_Base;
    class AK101 : AK101_Base
    {
        attachments[] = {"weaponButtstockAK", "WeaponHandguardAK", "weaponWrap", "weaponOpticsAK", "weaponFlashlight", "weaponMuzzleAK", "weaponBayonetAK", "weaponBipod"};
    };

    class AK74_Base;
    class AK74 : AK74_Base
    {
        attachments[] = {"weaponButtstockAK", "WeaponHandguardAK", "weaponWrap", "weaponOpticsAK", "weaponFlashlight", "weaponMuzzleAK", "weaponBayonetAK", "weaponBipod"};
    };
};

class CfgVehicles
{
    class Inventory_Base;
    class BDE_Bipod : Inventory_Base
    {
        scope = 2;
        displayName = "Rail Bipod";
        descriptionShort = "Rail-mounted bipod that deploys automatically while prone, reducing weapon sway and recoil.";
        model = "BDE_Bipod\Models\BDE_Bipod.p3d";
        inventorySlot[] = {"weaponBipod"};
        rotationFlags = 17;
        weight = 376;
        itemSize[] = {3, 1};
        repairableWithKits[] = {1};
        repairCosts[] = {25};
        dispersionModifier = 0;
        dexterityModifier = -0.2;
        recoilModifier[] = {1, 1, 1};
        swayModifier[] = {1, 1, 1};
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"BDE_Bipod\data\bipod_co.paa"};
        hiddenSelectionsMaterials[] = {"BDE_Bipod\data\bipod.rvmat"};
        class AnimationSources
        {
            class left_leg_deploy
            {
                source = "user";
                initPhase = 0;
                animPeriod = 0.35;
            };
            class right_leg_deploy : left_leg_deploy {};
            class left_leg_extend : left_leg_deploy {};
            class right_leg_extend : left_leg_deploy {};
        };
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 100;
                    RefTexsMats[] = {"bde_bipod\data\bipod.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_Bipod\data\bipod.rvmat"}},
                        {0.7, {"BDE_Bipod\data\bipod.rvmat"}},
                        {0.5, {"BDE_Bipod\data\bipod_damage.rvmat"}},
                        {0.3, {"BDE_Bipod\data\bipod_damage.rvmat"}},
                        {0.0, {"BDE_Bipod\data\bipod_destruct.rvmat"}}
                    };
                };
            };
        };
		
		s_recoilControlStabilityX = -0.05;
		s_recoilControlStabilityY = -0.05;
		s_recoilControlMisalignmentX = -0.0;
		s_recoilControlMisalignmentY = -0.01;
    };
};
