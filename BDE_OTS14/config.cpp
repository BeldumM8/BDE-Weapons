class CfgPatches
{
    class BDE_OTS14
    {
        units[] =
        {
            "BDE_OTS14_Foregrip",
            "BDE_OTS14_Suppressor"
        };
        weapons[] =
        {
            "BDE_OTS14_Groza"
        };
        requiredVersion = 0.1;
        requiredAddons[] =
        {
            "DZ_Data",
            "DZ_Weapons_Firearms_Famas",
            "DZ_Weapons_Magazines",
            "DZ_Weapons_Muzzles",
            "DZ_Weapons_Optics"
        };
    };
};

class CfgMods
{
    class BDE_OTS14
    {
        type = "mod";
        dependencies[] =
        {
            "World"
        };

        class defs
        {
            class worldScriptModule
            {
                value = "";
                files[] =
                {
                    "BDE_OTS14/Scripts/4_World"
                };
            };
        };
    };
};

class CfgSlots
{
    class Slot_BDE_OTS14_Suppressor
    {
        name = "BDE_OTS14_Suppressor";
        displayName = "Groza suppressor";
        ghostIcon = "set:dayz_inventory image:suppressor";
    };

    class Slot_BDE_OTS14_Sight
    {
        name = "BDE_OTS14_Sight";
        displayName = "Groza optic";
        ghostIcon = "set:dayz_inventory image:weaponoptics";
    };

    class Slot_BDE_OTS14_Foregrip
    {
        name = "BDE_OTS14_Foregrip";
        displayName = "Groza foregrip";
        ghostIcon = "set:dayz_inventory image:weaponhandguard";
    };

    class Slot_BDE_OTS14_Launcher
    {
        name = "BDE_OTS14_Launcher";
        displayName = "Groza launcher";
        ghostIcon = "set:dayz_inventory image:weaponhandguard";
    };
};

class Mode_SemiAuto;

class Mode_FullAuto;

class OpticsInfoRifle;

class CfgWeapons
{
    class Rifle_Base;

    class BDE_OTS14_Groza_Base : Rifle_Base
    {
        scope = 0;
        displayName = "OTs-14 Groza";
        descriptionShort = "Modular 9x39 mm bullpup rifle.";
        model = "BDE_OTS14\Models\Groza.p3d";
        weight = 2700;
        itemSize[] = {5, 3};
        absorbency = 0;
        repairableWithKits[] = {1};
        repairCosts[] = {25};
        barrelArmor = 1.667;
        WeaponLength = 0.62;
        weaponStateAnim = "dz\anims\anm\player\reloads\Famas\w_famas_states.anm";
        chamberSize = 1;
        chamberedRound = "";
        chamberableFrom[] =
        {
            "Ammo_9x39",
            "Ammo_9x39AP"
        };
        magazines[] =
        {
            "Mag_BDE_OTS14_20Rnd"
        };
        magazineSwitchTime = 0.38;
        ejectType = 1;
        attachments[] =
        {
            "BDE_OTS14_Foregrip",
            "BDE_OTS14_Suppressor",
            "BDE_OTS14_Launcher",
            "BDE_OTS14_Sight"
        };
        hiddenSelections[] =
        {
            "camo"
        };
        simpleHiddenSelections[] =
        {
            "lower_receiver",
            "muzzle",
            "bullet",
            "magazine"
        };
        hiddenSelectionsTextures[] =
        {
            "BDE_OTS14\Data\groza_co.paa"
        };
        recoilModifier[] = {1, 1, 1};
        swayModifier[] = {2, 2, 1.1};
        modes[] =
        {
            "SemiAuto",
            "FullAuto",
            "Launcher"
        };
        BDE_USL_Compatible = 1;
        BDE_USL_SettingsGroup = "BDE";
        BDE_USL_ProjectileSpawnClearance = 0;
        BDE_USL_LauncherSlot = "BDE_OTS14_Launcher";
        BDE_USL_Types[] =
        {
            "BDE_OTS14_Launcher"
        };
        BDE_USL_HandguardSlot = "";
        BDE_USL_BlockedSlots[] =
        {
            "BDE_OTS14_Foregrip"
        };
        BDE_GP25AllowedHandguards[] = {};
        BDE_GP25BlockedAttachments[] = {};

        class Launcher : Mode_SemiAuto
        {
            displayName = "Launcher";
            reloadTime = 1;
            dispersion = 0.025;
        };

        class SemiAuto : Mode_SemiAuto
        {
            soundSetShot[] =
            {
                "ots14_Shot_SoundSet",
                "ots14_Tail_SoundSet",
                "ots14_InteriorTail_SoundSet"
            };
            soundSetShotExt[] =
            {
                {
                    "ots14_silencer_SoundSet",
                    "ots14_silencerTail_SoundSet",
                    "ots14_silencerInteriorTail_SoundSet"
                }
            };
            reloadTime = 0.1;
            recoil = "recoil_VSS";
            recoilProne = "recoil_VSS_prone";
            dispersion = 0.0021;
            magazineSlot = "magazine";
        };

        class FullAuto : Mode_FullAuto
        {
            soundSetShot[] =
            {
                "ots14_Shot_SoundSet",
                "ots14_Tail_SoundSet",
                "ots14_InteriorTail_SoundSet"
            };
            soundSetShotExt[] =
            {
                {
                    "ots14_silencer_SoundSet",
                    "ots14_silencerTail_SoundSet",
                    "ots14_silencerInteriorTail_SoundSet"
                }
            };
            reloadTime = 0.085;
            recoil = "recoil_VSS";
            recoilProne = "recoil_VSS_prone";
            dispersion = 0.0021;
            magazineSlot = "magazine";
        };

        class OpticsInfoRifle
        {
            memoryPointCamera = "eye";
            discreteDistance[] = {100, 200};
            discreteDistanceInitIndex = 0;
            modelOptics = "-";
            distanceZoomMin = 100;
            distanceZoomMax = 200;
        };

        class Particles
        {
            class OnFire
            {
                class MuzzleFlash
                {
                    overrideParticle = "weapon_shot_ump45_01";
                    ignoreIfSuppressed = 1;
                    illuminateWorld = 1;
                };

                class SmokeCloud
                {
                    overrideParticle = "weapon_shot_winded_smoke";
                };
            };
        };

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 300;
                    RefTexsMats[] = {"BDE_OTS14\Data\groza.rvmat"};
                    healthLevels[] =
                    {
                        {1, {"BDE_OTS14\Data\groza.rvmat"}},
                        {0.7, {"BDE_OTS14\Data\groza.rvmat"}},
                        {0.5, {"BDE_OTS14\Data\groza_damage.rvmat"}},
                        {0.3, {"BDE_OTS14\Data\groza_damage.rvmat"}},
                        {0, {"BDE_OTS14\Data\groza_destruct.rvmat"}}
                    };
                };
            };
        };
		
		s_recoilControlStabilityX = 0.6;
		s_recoilControlStabilityY = 0.6;
		s_recoilControlMisalignmentX = 0.6;
		s_recoilControlMisalignmentY = 0.6;
		s_recoilControlKick = 0.6;
    };

    class BDE_OTS14_Groza : BDE_OTS14_Groza_Base
    {
        scope = 2;
    };
};

class CfgMagazines
{
    class Mag_Groza_20Rnd;

    class Mag_BDE_OTS14_20Rnd : Mag_Groza_20Rnd
    {
        scope = 2;
        displayName = "Groza 20-round magazine";
        model = "BDE_OTS14\Models\Groza_Magazine.p3d";
        hiddenSelections[] =
        {
            "camo"
        };
        hiddenSelectionsTextures[] =
        {
            "BDE_OTS14\Data\groza_co.paa"
        };

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 100;
                    RefTexsMats[] = {"BDE_OTS14\Data\groza.rvmat"};
                    healthLevels[] =
                    {
                        {1, {"BDE_OTS14\Data\groza.rvmat"}},
                        {0.7, {"BDE_OTS14\Data\groza.rvmat"}},
                        {0.5, {"BDE_OTS14\Data\groza_damage.rvmat"}},
                        {0.3, {"BDE_OTS14\Data\groza_damage.rvmat"}},
                        {0, {"BDE_OTS14\Data\groza_destruct.rvmat"}}
                    };
                };
            };
        };
    };
};

class CfgVehicles
{
    class GrozaOptic;

    class BDE_OTS14_Sight : GrozaOptic
    {
        scope = 2;
        displayName = "Groza 4x optic";
        model = "BDE_OTS14\Models\Groza_Sight.p3d";
        inventorySlot[] =
        {
            "BDE_OTS14_Sight"
        };
        hiddenSelections[] = {};
        hiddenSelectionsTextures[] = {};

        class OpticsInfo
        {
            useModelOptics = 1;
            modelOptics = "\DZ\weapons\attachments\optics\opticview_longrange.p3d";
            preloadOpticType = "Preload2DOptic_Longrange";
            memoryPointCamera = "eyeScope";
            cameraDir = "cameraDir";
            opticsDisablePeripherialVision = 0.67;
            opticsFlare = 1;
            opticsPPEffects[] =
            {
                "OpticsCHAbera5",
                "OpticsBlur3"
            };
            distanceZoomMin = 100;
            distanceZoomMax = 400;
            discreteDistance[] = {100, 200, 400};
            discreteDistanceInitIndex = 1;
            PPMaskProperties[] = {0.5, 0.5, 0.4, 0.05};
            PPLensProperties[] = {1, 0.15, 0, 0};
            PPBlurProperties = 0.2;
            opticsZoomMin = "0.3926/4";
            opticsZoomMax = "0.3926/4";
            opticsZoomInit = "0.3926/4";
        };

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 100;
                    RefTexsMats[] = {"BDE_OTS14\Data\groza_attachments.rvmat"};
                    healthLevels[] =
                    {
                        {1, {"BDE_OTS14\Data\groza_attachments.rvmat"}},
                        {0.7, {"BDE_OTS14\Data\groza_attachments.rvmat"}},
                        {0.5, {"BDE_OTS14\Data\groza_attachments_damage.rvmat"}},
                        {0.3, {"BDE_OTS14\Data\groza_attachments_damage.rvmat"}},
                        {0, {"BDE_OTS14\Data\groza_attachments_destruct.rvmat"}}
                    };
                };
            };
        };
		
		s_isFullscreen = 1;
		s_showEnterMisalignment = 1;
		s_pipRadius = 1;
		s_pipMagnification = 0.314;
		s_pipBlur = 0.01;
		s_pipChromAber = 0.2;
    };

    class Inventory_Base;

    class M4_Suppressor;

    class BDE_OTS14_Foregrip : Inventory_Base
    {
        scope = 2;
        displayName = "Groza foregrip";
        model = "BDE_OTS14\Models\Groza_Foregrip.p3d";
        inventorySlot[] =
        {
            "BDE_OTS14_Foregrip"
        };
        weight = 200;
        itemSize[] = {2, 2};
        rotationFlags = 17;
        repairableWithKits[] = {1};
        repairCosts[] = {25};
        hiddenSelections[] =
        {
            "camo"
        };
        hiddenSelectionsTextures[] =
        {
            "BDE_OTS14\Data\groza_attachments_co.paa"
        };

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 150;
                    RefTexsMats[] = {"BDE_OTS14\Data\groza_attachments.rvmat"};
                    healthLevels[] =
                    {
                        {1, {"BDE_OTS14\Data\groza_attachments.rvmat"}},
                        {0.7, {"BDE_OTS14\Data\groza_attachments.rvmat"}},
                        {0.5, {"BDE_OTS14\Data\groza_attachments_damage.rvmat"}},
                        {0.3, {"BDE_OTS14\Data\groza_attachments_damage.rvmat"}},
                        {0, {"BDE_OTS14\Data\groza_attachments_destruct.rvmat"}}
                    };
                };
            };
        };
		
		s_recoilControlStabilityX = 0.2;
		s_recoilControlStabilityY = 0.2;
		s_recoilControlMisalignmentX = 0.55;
		s_recoilControlMisalignmentY = 0.45;
    };

    class BDE_OTS14_Suppressor : M4_Suppressor
    {
        scope = 2;
        displayName = "Groza suppressor";
        model = "BDE_OTS14\Models\Groza_Suppressor.p3d";
        inventorySlot[] =
        {
            "BDE_OTS14_Suppressor"
        };
        weight = 500;
        itemSize[] = {3, 1};
        hiddenSelections[] =
        {
            "camo"
        };
        hiddenSelectionsTextures[] =
        {
            "BDE_OTS14\Data\groza_attachments_co.paa"
        };

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 150;
                    RefTexsMats[] = {"BDE_OTS14\Data\groza_attachments.rvmat"};
                    healthLevels[] =
                    {
                        {1, {"BDE_OTS14\Data\groza_attachments.rvmat"}},
                        {0.7, {"BDE_OTS14\Data\groza_attachments.rvmat"}},
                        {0.5, {"BDE_OTS14\Data\groza_attachments_damage.rvmat"}},
                        {0.3, {"BDE_OTS14\Data\groza_attachments_damage.rvmat"}},
                        {0, {"BDE_OTS14\Data\groza_attachments_destruct.rvmat"}}
                    };
                };
            };
        };
    };
};

class CfgNonAIVehicles
{
    class ProxyAttachment;

    class ProxyGroza_Sight : ProxyAttachment
    {
        scope = 2;
        simulation = "ProxyInventory";
        inventorySlot = "BDE_OTS14_Sight";
        model = "BDE_OTS14\Models\Groza_Sight.p3d";
    };

    class ProxyGroza_Foregrip : ProxyAttachment
    {
        scope = 2;
        simulation = "ProxyInventory";
        inventorySlot = "BDE_OTS14_Foregrip";
        model = "BDE_OTS14\Models\Groza_Foregrip.p3d";
    };

    class ProxyGroza_Suppressor : ProxyAttachment
    {
        scope = 2;
        simulation = "ProxyInventory";
        inventorySlot = "BDE_OTS14_Suppressor";
        model = "BDE_OTS14\Models\Groza_Suppressor.p3d";
    };

    class ProxyGroza_Magazine : ProxyAttachment
    {
        scope = 2;
        simulation = "ProxyInventory";
        inventorySlot = "magazine";
        model = "BDE_OTS14\Models\Groza_Magazine.p3d";
    };

    class ProxyGroza_LauncherSlot : ProxyAttachment
    {
        scope = 2;
        simulation = "ProxyInventory";
        inventorySlot = "BDE_OTS14_Launcher";
        model = "BDE_OTS14\Models\Groza_LauncherSlot.p3d";
    };
};
