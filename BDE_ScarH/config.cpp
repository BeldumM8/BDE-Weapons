class CfgPatches
{
    class BDE_ScarH
    {
        units[] =
        {
            "BDE_ScarH_Foregrip_FDE",
            "BDE_ScarH_Foregrip_Black",
            "BDE_ScarH_Suppressor_Olive",
            "BDE_ScarH_Suppressor_Black",
            "Mag_BDE_ScarH_30Rnd_FDE",
            "Mag_BDE_ScarH_30Rnd_Black"
        };
        weapons[] =
        {
            "SCARH",
            "SCARH_Black"
        };
        requiredVersion = 0.1;
        requiredAddons[] =
        {
            "DZ_Data",
            "DZ_Weapons_Firearms_SCARH",
            "DZ_Weapons_Magazines",
            "DZ_Weapons_Muzzles",
            "DZ_Weapons_Supports"
        };
    };
};

class CfgMods
{
    class BDE_ScarH
    {
        dir = "BDE_ScarH";
        name = "BDE SCAR-H";
        type = "mod";
        dependencies[] = {"World"};

        class defs
        {
            class worldScriptModule
            {
                value = "";
                files[] = {"BDE_ScarH/Scripts/4_World"};
            };
        };
    };
};

class CfgSlots
{
    class Slot_BDE_SideRail
    {
        name = "BDE_SideRail";
        displayName = "Side Rail Sight";
        ghostIcon = "set:dayz_inventory image:weaponoptics";
    };
};

class Mode_Safe;
class Mode_SemiAuto;
class Mode_Burst;
class Mode_FullAuto;
class OpticsInfoRifle;

class CfgWeapons
{
    class SCARH_Base;

    class SCARH : SCARH_Base
    {
        scope = 2;
        displayName = "$STR_cfgWeapons_SCARH0";
        descriptionShort = "$STR_cfgWeapons_SCARH1";
        model = "\BDE_ScarH\Models\Scar_H.p3d";
        attachments[] = {"weaponButtstockSCAR", "weaponWrap", "weaponOptics", "suppressorImpro", "Scarh_FrontSight", "weaponFlashlight", "weaponBipod", "BDE_SideRail"};
        BDE_SideRailCompatible = 1;
        magazines[] = {"Mag_SCARH_20Rnd", "Mag_SCARH_20Rnd_Black", "Mag_BDE_ScarH_30Rnd_FDE", "Mag_BDE_ScarH_30Rnd_Black"};
        itemSize[] = {8, 3};

        simpleHiddenSelections[] =
        {
            "hide_barrel",
            "lower_railcover",
            "right_railcover",
            "left_railcover"
        };

        hiddenSelections[] = {"camo", "bolt", "firemode", "trigger", "lower_railcover", "left_railcover", "right_railcover"};
        hiddenSelectionsTextures[] = {"BDE_ScarH\data\scarh_fde_co.paa", "BDE_ScarH\data\vanilla_scarh_mat2_fde_co.paa", "BDE_ScarH\data\vanilla_scarh_mat2_fde_co.paa", "BDE_ScarH\data\vanilla_scarh_mat2_fde_co.paa", "BDE_ScarH\data\scarh_accessories_fde_co.paa", "BDE_ScarH\data\scarh_accessories_fde_co.paa", "BDE_ScarH\data\scarh_accessories_fde_co.paa"};
        hiddenSelectionsMaterials[] = {"BDE_ScarH\data\scarh_fde.rvmat", "BDE_ScarH\data\vanilla_scarh_mat2_fde.rvmat", "BDE_ScarH\data\vanilla_scarh_mat2_fde.rvmat", "BDE_ScarH\data\vanilla_scarh_mat2_fde.rvmat", "BDE_ScarH\data\scarh_accessories_fde.rvmat", "BDE_ScarH\data\scarh_accessories_fde.rvmat", "BDE_ScarH\data\scarh_accessories_fde.rvmat"};

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 300;
                    RefTexsMats[] = {"bde_scarh\data\scarh_fde.rvmat", "bde_scarh\data\vanilla_scarh_mat2_fde.rvmat", "bde_scarh\data\scarh_accessories_fde.rvmat", "dz\weapons\attachments\magazine\data\magazine_scarh_20rnd.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_ScarH\data\scarh_fde.rvmat", "BDE_ScarH\data\vanilla_scarh_mat2_fde.rvmat", "BDE_ScarH\data\scarh_accessories_fde.rvmat", "dz\weapons\attachments\magazine\data\magazine_scarh_20rnd.rvmat"}},
                        {0.7, {"BDE_ScarH\data\scarh_fde.rvmat", "BDE_ScarH\data\vanilla_scarh_mat2_fde.rvmat", "BDE_ScarH\data\scarh_accessories_fde.rvmat", "dz\weapons\attachments\magazine\data\magazine_scarh_20rnd.rvmat"}},
                        {0.5, {"BDE_ScarH\data\scarh_fde_damage.rvmat", "BDE_ScarH\data\vanilla_scarh_mat2_fde_damage.rvmat", "BDE_ScarH\data\scarh_accessories_fde_damage.rvmat", "dz\weapons\attachments\magazine\data\magazine_scarh_20rnd_damage.rvmat"}},
                        {0.3, {"BDE_ScarH\data\scarh_fde_damage.rvmat", "BDE_ScarH\data\vanilla_scarh_mat2_fde_damage.rvmat", "BDE_ScarH\data\scarh_accessories_fde_damage.rvmat", "dz\weapons\attachments\magazine\data\magazine_scarh_20rnd_damage.rvmat"}},
                        {0.0, {"BDE_ScarH\data\scarh_fde_destruct.rvmat", "BDE_ScarH\data\vanilla_scarh_mat2_fde_destruct.rvmat", "BDE_ScarH\data\scarh_accessories_fde_destruct.rvmat", "dz\weapons\attachments\magazine\data\magazine_scarh_20rnd_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class SCARH_Black : SCARH
    {
        scope = 2;
        hiddenSelectionsTextures[] = {"BDE_ScarH\data\scarh_black_co.paa", "BDE_ScarH\data\vanilla_scarh_mat2_black_co.paa", "BDE_ScarH\data\vanilla_scarh_mat2_black_co.paa", "BDE_ScarH\data\vanilla_scarh_mat2_black_co.paa", "BDE_ScarH\data\scarh_accessories_black_co.paa", "BDE_ScarH\data\scarh_accessories_black_co.paa", "BDE_ScarH\data\scarh_accessories_black_co.paa"};
        hiddenSelectionsMaterials[] = {"BDE_ScarH\data\scarh_black.rvmat", "BDE_ScarH\data\vanilla_scarh_mat2_black.rvmat", "BDE_ScarH\data\vanilla_scarh_mat2_black.rvmat", "BDE_ScarH\data\vanilla_scarh_mat2_black.rvmat", "BDE_ScarH\data\scarh_accessories_black.rvmat", "BDE_ScarH\data\scarh_accessories_black.rvmat", "BDE_ScarH\data\scarh_accessories_black.rvmat"};

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 250;
                    RefTexsMats[] = {"bde_scarh\data\scarh_fde.rvmat", "bde_scarh\data\vanilla_scarh_mat2_fde.rvmat", "bde_scarh\data\scarh_accessories_fde.rvmat", "dz\weapons\attachments\magazine\data\magazine_scarh_20rnd.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_ScarH\data\scarh_black.rvmat", "BDE_ScarH\data\vanilla_scarh_mat2_black.rvmat", "BDE_ScarH\data\scarh_accessories_black.rvmat", "dz\weapons\attachments\magazine\data\magazine_scarh_20rnd.rvmat"}},
                        {0.7, {"BDE_ScarH\data\scarh_black.rvmat", "BDE_ScarH\data\vanilla_scarh_mat2_black.rvmat", "BDE_ScarH\data\scarh_accessories_black.rvmat", "dz\weapons\attachments\magazine\data\magazine_scarh_20rnd.rvmat"}},
                        {0.5, {"BDE_ScarH\data\scarh_black_damage.rvmat", "BDE_ScarH\data\vanilla_scarh_mat2_black_damage.rvmat", "BDE_ScarH\data\scarh_accessories_black_damage.rvmat", "dz\weapons\attachments\magazine\data\magazine_scarh_20rnd_damage.rvmat"}},
                        {0.3, {"BDE_ScarH\data\scarh_black_damage.rvmat", "BDE_ScarH\data\vanilla_scarh_mat2_black_damage.rvmat", "BDE_ScarH\data\scarh_accessories_black_damage.rvmat", "dz\weapons\attachments\magazine\data\magazine_scarh_20rnd_damage.rvmat"}},
                        {0.0, {"BDE_ScarH\data\scarh_black_destruct.rvmat", "BDE_ScarH\data\vanilla_scarh_mat2_black_destruct.rvmat", "BDE_ScarH\data\scarh_accessories_black_destruct.rvmat", "dz\weapons\attachments\magazine\data\magazine_scarh_20rnd_destruct.rvmat"}}
                    };
                };
            };
        };
    };
};

class CfgNonAIVehicles
{
    class ProxyAttachment;
    class ProxySideRail : ProxyAttachment
    {
        scope = 2;
        simulation = "ProxyInventory";
        inventorySlot = "BDE_SideRail";
        model = "\BDE_ScarH\Models\Proxies\SideRail.p3d";
    };
};

class CfgVehicles
{
    class Inventory_Base;

    // Vanilla stock models with finishes matched to the replacement SCAR-H.
    class SCAR_StockBttstck : Inventory_Base
    {
        hiddenSelectionsTextures[] = {"BDE_ScarH\data\stocks\buttstock_scar_stock_co.paa"};
    };

    class SCAR_StockBttstck_Black : SCAR_StockBttstck
    {
        hiddenSelectionsTextures[] = {"BDE_ScarH\data\stocks\buttstock_scar_stock_black_co.paa"};
    };

    class SCAR_PrecisionBttstck : Inventory_Base
    {
        hiddenSelectionsTextures[] = {"BDE_ScarH\data\stocks\buttstock_scar_precision_co.paa"};
    };

    class SCAR_PrecisionBttstck_Black : SCAR_PrecisionBttstck
    {
        hiddenSelectionsTextures[] = {"BDE_ScarH\data\stocks\buttstock_scar_precision_black_co.paa"};
    };


    class BDE_ScarH_Foregrip_FDE : Inventory_Base
    {
        scope = 2;
        displayName = "SCAR-H Foregrip (FDE)";
        descriptionShort = "Vertical foregrip for the SCAR-H.";
        model = "\BDE_ScarH\Models\Foregrip_1.p3d";
        weight = 130;
        itemSize[] = {2, 1};
        inventorySlot[] = {"weaponBipod"};
        class InventorySlotsOffsets
        {
            class weaponBipod
            {
                position[] = {0.007, 0.012, 0};
                orientation[] = {0, 0, 0};
            };
        };
        rotationFlags = 17;
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"BDE_ScarH\data\scarh_accessories_fde_co.paa"};
        hiddenSelectionsMaterials[] = {"BDE_ScarH\data\scarh_accessories_fde.rvmat"};

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 100;
                    RefTexsMats[] = {"bde_scarh\data\scarh_accessories_fde.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_ScarH\data\scarh_accessories_fde.rvmat"}},
                        {0.7, {"BDE_ScarH\data\scarh_accessories_fde.rvmat"}},
                        {0.5, {"BDE_ScarH\data\scarh_accessories_fde_damage.rvmat"}},
                        {0.3, {"BDE_ScarH\data\scarh_accessories_fde_damage.rvmat"}},
                        {0.0, {"BDE_ScarH\data\scarh_accessories_fde_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_ScarH_Foregrip_Black : BDE_ScarH_Foregrip_FDE
    {
        scope = 2;
        displayName = "SCAR-H Foregrip (Black)";
        hiddenSelectionsTextures[] = {"BDE_ScarH\data\scarh_accessories_black_co.paa"};
        hiddenSelectionsMaterials[] = {"BDE_ScarH\data\scarh_accessories_black.rvmat"};

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 100;
                    RefTexsMats[] = {"bde_scarh\data\scarh_accessories_fde.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_ScarH\data\scarh_accessories_black.rvmat"}},
                        {0.7, {"BDE_ScarH\data\scarh_accessories_black.rvmat"}},
                        {0.5, {"BDE_ScarH\data\scarh_accessories_black_damage.rvmat"}},
                        {0.3, {"BDE_ScarH\data\scarh_accessories_black_damage.rvmat"}},
                        {0.0, {"BDE_ScarH\data\scarh_accessories_black_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class M4_Suppressor;
    class BDE_ScarH_Suppressor_Olive : M4_Suppressor
    {
        scope = 2;
        displayName = "SCAR-H Wrapped Suppressor (Olive)";
        descriptionShort = "Wrapped suppressor for the SCAR-H.";
        model = "BDE_ScarH\Models\Scar_H_Suppressor.p3d";
        inventorySlot[] = {"suppressorImpro"};
        weight = 450;
        itemSize[] = {3, 1};
        itemModelLength = 0.187;

        soundIndex = 2;
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"BDE_ScarH\data\Suppressor\suppressor_olive_co.paa"};
        hiddenSelectionsMaterials[] = {"BDE_ScarH\data\Suppressor\suppressor_olive.rvmat"};
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 4;
                    RefTexsMats[] = {"bde_scarh\data\suppressor\suppressor_olive.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_ScarH\data\Suppressor\suppressor_olive.rvmat"}},
                        {0.7, {"BDE_ScarH\data\Suppressor\suppressor_olive.rvmat"}},
                        {0.5, {"BDE_ScarH\data\Suppressor\suppressor_olive_damage.rvmat"}},
                        {0.3, {"BDE_ScarH\data\Suppressor\suppressor_olive_damage.rvmat"}},
                        {0.0, {"BDE_ScarH\data\Suppressor\suppressor_olive_destruct.rvmat"}}
                    };
                };
            };
        };
    };
    class BDE_ScarH_Suppressor_Black : BDE_ScarH_Suppressor_Olive
    {
        displayName = "SCAR-H Wrapped Suppressor (Black)";
        hiddenSelectionsTextures[] = {"BDE_ScarH\data\Suppressor\suppressor_black_co.paa"};
        hiddenSelectionsMaterials[] = {"BDE_ScarH\data\Suppressor\suppressor_black.rvmat"};
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 4;
                    RefTexsMats[] = {"bde_scarh\data\suppressor\suppressor_olive.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_ScarH\data\Suppressor\suppressor_black.rvmat"}},
                        {0.7, {"BDE_ScarH\data\Suppressor\suppressor_black.rvmat"}},
                        {0.5, {"BDE_ScarH\data\Suppressor\suppressor_black_damage.rvmat"}},
                        {0.3, {"BDE_ScarH\data\Suppressor\suppressor_black_damage.rvmat"}},
                        {0.0, {"BDE_ScarH\data\Suppressor\suppressor_black_destruct.rvmat"}}
                    };
                };
            };
        };
    };
};

class CfgMagazines
{
    class Mag_SCARH_20Rnd;
    class Mag_BDE_ScarH_30Rnd_FDE : Mag_SCARH_20Rnd
    {
        scope = 2;
        displayName = "SCAR-H 30rd Magazine (FDE)";
        descriptionShort = "Extended 30-round SCAR-H magazine for .308 Winchester ammunition.";
        model = "BDE_ScarH\Models\Scar_H_30rnd.p3d";
        count = 30;
        weight = 400;
        itemSize[] = {1, 3};
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"BDE_ScarH\data\scarh_fde_co.paa"};
        hiddenSelectionsMaterials[] = {"BDE_ScarH\data\scarh_fde.rvmat"};
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 100;
                    RefTexsMats[] = {"BDE_ScarH\data\scarh_fde.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_ScarH\data\scarh_fde.rvmat"}},
                        {0.7, {"BDE_ScarH\data\scarh_fde.rvmat"}},
                        {0.5, {"BDE_ScarH\data\scarh_fde_damage.rvmat"}},
                        {0.3, {"BDE_ScarH\data\scarh_fde_damage.rvmat"}},
                        {0.0, {"BDE_ScarH\data\scarh_fde_destruct.rvmat"}}
                    };
                };
            };
        };
    };
    class Mag_BDE_ScarH_30Rnd_Black : Mag_BDE_ScarH_30Rnd_FDE
    {
        displayName = "SCAR-H 30rd Magazine (Black)";
        hiddenSelectionsTextures[] = {"BDE_ScarH\data\scarh_black_co.paa"};
        hiddenSelectionsMaterials[] = {"BDE_ScarH\data\scarh_black.rvmat"};
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 100;
                    RefTexsMats[] = {"BDE_ScarH\data\scarh_fde.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_ScarH\data\scarh_black.rvmat"}},
                        {0.7, {"BDE_ScarH\data\scarh_black.rvmat"}},
                        {0.5, {"BDE_ScarH\data\scarh_black_damage.rvmat"}},
                        {0.3, {"BDE_ScarH\data\scarh_black_damage.rvmat"}},
                        {0.0, {"BDE_ScarH\data\scarh_black_destruct.rvmat"}}
                    };
                };
            };
        };
    };
};
