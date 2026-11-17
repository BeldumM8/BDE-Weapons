class CfgPatches
{
    class BDE_RPG7
    {
        units[] =
        {
            "RPG7_Bipod",
            "RPG7_Sights",
            "RPG7_Optic",
            "BDE_Ammo_OG7",
            "BDE_Ammo_PG7",
            "BDE_Ammo_PG7R"
        };
        weapons[] =
        {
            "BDE_RPG7",
            "BDE_M72A7_LAW"
        };
        requiredVersion = 0.1;
        requiredAddons[] =
        {
            "DZ_Data",
            "DZ_Weapons_Firearms",
            "DZ_Weapons_Launchers_M79",
            "DZ_Weapons_Optics",
            "DZ_Weapons_Supports",
            "DZ_Weapons_Ammunition",
            "DZ_Weapons_Projectiles",
            "DZ_Weapons_Explosives",
            "DZ_Sounds_Effects"
        };
    };
};

class CfgMods
{
    class BDE_RPG7
    {
        name = "BDE RPG-7 Test 09";
        type = "mod";
        author = "Beldum";
        dependencies[] =
        {
            "Game",
            "World"
        };

        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] =
                {
                    "BDE_RPG7/Scripts/3_Game"
                };
            };
            class worldScriptModule
            {
                value = "";
                files[] =
                {
                    "BDE_RPG7/Scripts/4_World"
                };
            };
        };
    };
};

class CfgSoundShaders
{
    class BDE_RPG7_Launch_Exterior_SoundShader
    {
        samples[] =
        {
            {"BDE_RPG7\sounds\RocketLauncher_Shot05_A.ogg", 1}
        };
        volume = "((meadows + sea + forest + houses + trees)/(forest + houses + meadows + sea + trees)) * (1-interior)";
        range = 3500;
        rangeCurve[] =
        {
            {0, 1},
            {0.02, 1},
            {0.08, 0.85},
            {0.2, 0.6},
            {0.5, 0.3},
            {0.8, 0.12},
            {1, 0}
        };
    };

    class BDE_RPG7_Launch_Interior_SoundShader
    {
        samples[] =
        {
            {"BDE_RPG7\sounds\RocketLauncher_Shot05_A.ogg", 1}
        };
        volume = "interior";
        range = 180;
        rangeCurve[] =
        {
            {0, 1},
            {0.35, 0.75},
            {0.7, 0.3},
            {1, 0}
        };
    };

    class BDE_RPG7_RocketFly_SoundShader
    {
        samples[] =
        {
            {"BDE_RPG7\sounds\rocket_fly1.ogg", 1}
        };
        volume = "((meadows + sea + forest + houses + trees)/(forest + houses + meadows + sea + trees)) * (1-interior)";
        range = 1800;
        rangeCurve[] =
        {
            {0, 1},
            {0.03, 1},
            {0.15, 0.8},
            {0.4, 0.5},
            {0.7, 0.22},
            {1, 0}
        };
    };
};

class CfgSoundSets
{
    class BDE_RPG7_Launch_SoundSet
    {
        soundShaders[] =
        {
            "BDE_RPG7_Launch_Exterior_SoundShader"
        };
        volumeFactor = 1;
        volumeCurve = "RifleShotCurve";
        sound3DProcessingType = "WeaponMediumShot3DProcessingType";
        distanceFilter = "weaponShotDistanceFreqAttenuationFilter";
        occlusionFactor = 0.6;
        obstructionFactor = 0.6;
        spatial = 1;
        doppler = 0;
        loop = 0;
        soundShadersLimit = 1;
        soundObjectsLimit = 4;
    };

    class BDE_RPG7_Launch_Interior_SoundSet
    {
        soundShaders[] =
        {
            "BDE_RPG7_Launch_Interior_SoundShader"
        };
        volumeFactor = 1;
        volumeCurve = "RifleShot_Interior_Curve";
        sound3DProcessingType = "WeaponMediumShot3DProcessingType";
        distanceFilter = "weaponShotDistanceFreq_INT_AttenuationFilter";
        occlusionFactor = 0.6;
        obstructionFactor = 0.6;
        spatial = 1;
        doppler = 0;
        loop = 0;
        soundShadersLimit = 1;
        soundObjectsLimit = 4;
    };

    class BDE_RPG7_RocketFly_SoundSet
    {
        soundShaders[] =
        {
            "BDE_RPG7_RocketFly_SoundShader"
        };
        volumeFactor = 1;
        sound3DProcessingType = "WeaponMediumShot3DProcessingType";
        distanceFilter = "weaponShotDistanceFreqAttenuationFilter";
        occlusionFactor = 0.35;
        obstructionFactor = 0.35;
        spatial = 1;
        doppler = 1;
        loop = 1;
        soundShadersLimit = 1;
        soundObjectsLimit = 32;
    };
};

class CfgSlots
{
    class Slot_BDE_RPG7_Bipod
    {
        name = "BDE_RPG7_Bipod";
        displayName = "RPG-7 Bipod";
        ghostIcon = "bipod";
    };

    class Slot_BDE_RPG7_Sights
    {
        name = "BDE_RPG7_Sights";
        displayName = "RPG-7 Sights";
        show = 0;
    };
    class Slot_BDE_LAW_Parts
    {
        name = "BDE_LAW_Parts";
        displayName = "LAW mechanism";
        show = 0;
    };

};

class Mode_Single;
class OpticsInfoRifle;

class CfgWeapons
{
    class Rifle_Base;

    class BDE_RPG7 : Rifle_Base
    {
        scope = 2;
        displayName = "RPG-7V";
        descriptionShort = "The RPG-7V is a Soviet-designed, portable, shoulder-fired, muzzle-loaded anti-tank grenade launcher that fires fin-stabilized, rocket-assisted shaped-charge warheads.";
        model = "BDE_RPG7\models\RPG7.p3d";
        weight = 6300;
        itemSize[] =
        {
            10, 4
        };
        // Inherit Rifle_Base slots, including slots added by storage mods.
        attachments[] =
        {
            "weaponOptics",
            "BDE_RPG7_Sights",
            "BDE_RPG7_Bipod"
        };
        repairableWithKits[] =
        {
            1
        };
        repairCosts[] =
        {
            25
        };
        WeaponLength = 0.95;
        ObstructionDistance = 0.7;
        barrelArmor = 5;
        simpleHiddenSelections[] =
        {
            "rocket_og7",
            "rocket_pg7",
            "rocket_pg7r"
        };
        chamberSize = 1;
        chamberedRound = "";
        chamberableFrom[] =
        {
            "BDE_Ammo_OG7",
            "BDE_Ammo_PG7",
            "BDE_Ammo_PG7R"
        };
        magazines[] = {};
        reloadAction = "ReloadIZH18";
        shotAction = "";
        DisplayMagazine = 0;
        ejectType = 3;
        initSpeedMultiplier = 1;
        recoilModifier[] =
        {
            0.3, 0.3, 0.3
        };
        swayModifier[] =
        {
            1.4, 1.4, 1.4
        };
        s_recoilControlStabilityX = 0.8;
        s_recoilControlStabilityY = 0.8;
        s_recoilControlMisalignmentX = 0.8;
        s_recoilControlMisalignmentY = 0.8;
        s_recoilControlKick = 1.0;
        PPDOFProperties[] =
        {
            0, 0.5, 10, 170, 4, 10
        };
        modes[] =
        {
            "Single"
        };

        class Single : Mode_Single
        {
            soundSetShot[] =
            {
                "BDE_RPG7_Launch_SoundSet",
                "BDE_RPG7_Launch_Interior_SoundSet"
            };
            soundSetShotExt[] = {};
            reloadTime = 1;
            dispersion = 0.002;
        };

        class NoiseShoot
        {
            strength = 80;
            type = "shot";
        };

        class OpticsInfo : OpticsInfoRifle
        {
            memoryPointCamera = "eye";
            cameraDir = "look";
            modelOptics = "-";
            discreteDistance[] =
            {
                0
            };
            discreteDistanceInitIndex = 0;
            distanceZoomMin = 0;
            distanceZoomMax = 0;
        };

        weaponStateAnim = "dz\anims\anm\player\reloads\IZH18\w_izh18_states.anm";
        boneRemap[] =
        {
            "trigger",
            "Weapon_Trigger"
        };

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 500;
                    healthLevels[] =
                    {
                        {1, {}},
                        {0.7, {}},
                        {0.5, {}},
                        {0.3, {}},
                        {0, {}}
                    };
                };
            };
        };
    };
    class BDE_M72A7_LAW : BDE_RPG7
    {
        scope = 2;
        displayName = "M72A7 LAW";
        descriptionShort = "Single-use anti-armour launcher. Double tap Charge Fire Mechanism (Reload) button while standing to unfold or fold. Issued loaded; the tube is spent after firing.";
        model = "BDE_RPG7\models\LAW\M72A7_LAW_Tube.p3d";
        weight = 3500;
        itemSize[] =
        {
            6, 3
        };
        attachments[] =
        {
            "BDE_LAW_Parts"
        };
        repairableWithKits[] = {};
        repairCosts[] = {};
        simpleHiddenSelections[] = {};
        chamberableFrom[] = {};
        magazines[] = {};
        weaponStateAnim = "";
        boneRemap[] =
        {
            "trigger", "Weapon_Trigger"
        };
        WeaponLength = 0.65;
        ObstructionDistance = 0.5;


    };

    // Internal swap target. Fresh admin spawns are normalized to folded.
    class BDE_M72A7_LAW_Unfolded : BDE_M72A7_LAW
    {
        model = "BDE_RPG7\models\LAW\M72A7_LAW_Tube_Unfolded.p3d";
        scope = 1;
        itemSize[] =
        {
            9, 3
        };
        WeaponLength = 0.98;
        ObstructionDistance = 0.8;
    };

};

class CfgVehicles
{
    // Local reload props have no inventory, flight script or physics body.
    class HouseNoDestruct;

    class BDE_RPG7_ReloadProp : HouseNoDestruct
    {
        scope = 1;
        model = "BDE_RPG7\models\RPG7_PG7.p3d";
        displayName = "";
        mapSize = 0;
    };

    class BDE_RPG7_ReloadProp_OG7 : BDE_RPG7_ReloadProp
    {
        model = "BDE_RPG7\models\RPG7_OG7.p3d";
    };

    class BDE_RPG7_ReloadProp_PG7 : BDE_RPG7_ReloadProp
    {
    };

    class BDE_RPG7_ReloadProp_PG7R : BDE_RPG7_ReloadProp
    {
        model = "BDE_RPG7\models\RPG7_PG7R.p3d";
    };

    class Inventory_Base;
    class ItemOptics;

    class RPG7_Bipod : Inventory_Base
    {
        scope = 2;
        displayName = "RPG-7V Bipod";
        descriptionShort = "Bipod for the RPG-7V";
        model = "BDE_RPG7\models\RPG7_Bipod.p3d";
        weight = 700;
        itemSize[] =
        {
            2, 3
        };
        inventorySlot[] =
        {
            "BDE_RPG7_Bipod"
        };
        rotationFlags = 17;
        s_recoilControlStabilityX = 0.2;
        s_recoilControlStabilityY = 0.2;
        s_recoilControlMisalignmentX = 0.2;
        s_recoilControlMisalignmentY = 0.2;

        class AnimationSources
        {
            class leg_left_deploy
            {
                source = "user";
                initPhase = 0;
                animPeriod = 0.3;
            };

            class leg_right_deploy : leg_left_deploy
            {
            };
        };
    };

    class RPG7_Sights : Inventory_Base
    {
        scope = 1;
        displayName = "RPG-7 Iron Sights";
        model = "BDE_RPG7\models\RPG7_Sights.p3d";
        descriptionShort = "Iron sights for the RPG-7V, Beldum loves you dear player <3";
        weight = 120;
        itemSize[] =
        {
            2, 1
        };
        inventorySlot[] =
        {
            "BDE_RPG7_Sights"
        };

        class AnimationSources
        {
            class front_sight_fold
            {
                source = "user";
                initPhase = 1;
                animPeriod = 0.3;
            };

            class rear_sight_fold : front_sight_fold
            {
            };
        };
    };

    class RPG7_Optic : ItemOptics
    {
        scope = 2;
        displayName = "PGO-7V Optic";
        descriptionShort = "PGO-7V optical sight for the RPG-7V.";
        model = "BDE_RPG7\models\RPG7_Optic.p3d";
        weight = 600;
        itemSize[] =
        {
            3, 2
        };
        inventorySlot[] =
        {
            "weaponOptics"
        };
        simulation = "itemoptics";
        memoryPointCamera = "eyeScope";
        cameraDir = "cameraDir";
        s_showEnterMisalignment = 0;
        s_isFullscreen = 1;
        s_pipRadius = 1.0;
        s_pipBlur = 0.02;
        s_pipChromAber = 0.2;
        s_nearPlaneOverride = 0.15;

        class AnimationSources
        {
            class optic_hide
            {
                source = "user";
                initPhase = 0;
                animPeriod = 0.01;
            };
        };

        class OpticsInfo
        {
            memoryPointCamera = "eyeScope";
            cameraDir = "cameraDir";
            useModelOptics = 1;
            modelOptics = "BDE_RPG7\models\PGO7_OpticView.p3d";
            opticsZoomMin = 0.15704;
            opticsZoomMax = 0.15704;
            opticsZoomInit = 0.15704;
            opticsDisablePeripherialVision = 0.67;
            opticsFlare = 1;
            opticsPPEffects[] =
            {
                "OpticsCHAbera5",
                "OpticsBlur3"
            };
            distanceZoomMin = 0;
            distanceZoomMax = 0;
            discreteDistance[] =
            {
                0
            };
            discreteDistanceInitIndex = 0;
            PPMaskProperties[] =
            {
                0.5, 0.5, 0.4, 0.05
            };
            PPLensProperties[] =
            {
                1, 0.15, 0, 0
            };
            PPBlurProperties = 0.2;
        };


        class OpticsInfoWeaponOverride
        {
            memoryPointCamera = "eyeIronsights";
            cameraDir = "cameraDirIronsights";
            opticsZoomMin = 0.52359998;
            opticsZoomMax = 0.52359998;
            opticsZoomInit = 0.52359998;
            distanceZoomMin = 0;
            distanceZoomMax = 0;
            discreteDistance[] =
            {
                0
            };
            discreteDistanceInitIndex = 0;
            PPDOFProperties[] =
            {
                1, 0.1, 20, 200, 4, 10
            };
        };
    };

    // Internal flight entities cannot be picked up and are not CE spawn classes.
    class BDE_RPG7_Flight : Inventory_Base
    {
        scope = 1;
        model = "BDE_RPG7\models\RPG7_PG7.p3d";
        displayName = "";
        itemSize[] =
        {
            1, 1
        };
        weight = 1;
        storageCategory = 0;
        carveNavmesh = 0;
    };

    class BDE_RPG7_Flight_OG7 : BDE_RPG7_Flight
    {
        model = "BDE_RPG7\models\RPG7_OG7.p3d";
    };

    class BDE_RPG7_Flight_PG7 : BDE_RPG7_Flight
    {
    };

    class BDE_RPG7_Flight_PG7R : BDE_RPG7_Flight
    {
        model = "BDE_RPG7\models\RPG7_PG7R.p3d";
    };
    class BDE_LAW_Parts : Inventory_Base
    {
        scope = 1;
        displayName = "LAW mechanism";
        model = "BDE_RPG7\models\LAW\M72A7_LAW_Parts.p3d";
        weight = 0;
        itemSize[] =
        {
            1, 1
        };
        inventorySlot[] =
        {
            "BDE_LAW_Parts"
        };
        class AnimationSources
        {
            class safety_slide
            {
                source = "user";
                initPhase = 0;
                animPeriod = 0.01;
            };
            class tube_extend
            {
                source = "user";
                initPhase = 0;
                animPeriod = 0.01;
            };
            class tube_cap_deploy
            {
                source = "user";
                initPhase = 0;
                animPeriod = 0.01;
            };
            class front_sight_deploy
            {
                source = "user";
                initPhase = 0;
                animPeriod = 0.01;
            };
            class rear_sight_deploy
            {
                source = "user";
                initPhase = 0;
                animPeriod = 0.01;
            };
            class sight_cover_hide
            {
                source = "user";
                initPhase = 0;
                animPeriod = 0.01;
            };
            class rocket_hide
            {
                source = "user";
                initPhase = 0;
                animPeriod = 0.01;
            };
        };
    };

    class BDE_LAW_Flight : BDE_RPG7_Flight_PG7
    {
        model = "BDE_RPG7\models\LAW\M72A7_LAW_Rocket.p3d";
        class AnimationSources
        {
            class fin_1_deploy
            {
                source = "user";
                initPhase = 0;
                animPeriod = 0.01;
            };
            class fin_2_deploy
            {
                source = "user";
                initPhase = 0;
                animPeriod = 0.01;
            };
            class fin_3_deploy
            {
                source = "user";
                initPhase = 0;
                animPeriod = 0.01;
            };
            class fin_4_deploy
            {
                source = "user";
                initPhase = 0;
                animPeriod = 0.01;
            };
            class fin_5_deploy
            {
                source = "user";
                initPhase = 0;
                animPeriod = 0.01;
            };
            class fin_6_deploy
            {
                source = "user";
                initPhase = 0;
                animPeriod = 0.01;
            };
        };
    };

};

class CfgMagazines
{
    class Ammo_40mm_Explosive;

    class BDE_Ammo_OG7 : Ammo_40mm_Explosive
    {
        scope = 2;
        displayName = "OG-7V Rocket";
        descriptionShort = "The OG-7V is a 40mm high-explosive fragmentation, anti-personnel projected grenade designed specifically for use with the RPG-7V launcher.";
        model = "BDE_RPG7\models\RPG7_OG7.p3d";
        ammo = "BDE_RPG7_Shot_OG7";
        weight = 2000;
        itemSize[] =
        {
            6, 2
        };
        count = 1;
        inventorySlot[] = {};

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 50;
                    healthLevels[] =
                    {
                        {1, {}},
                        {0.7, {}},
                        {0.5, {}},
                        {0.3, {}},
                        {0, {}}
                    };
                };
            };
        };
    };

    class BDE_Ammo_PG7 : BDE_Ammo_OG7
    {
        displayName = "PG-7 Rocket";
        descriptionShort = "The PG-7V is an 85mm, fin-stabilized, high-explosive anti-tank (HEAT) rocket designed specifically for use with the RPG-7V launcher.";
        model = "BDE_RPG7\models\RPG7_PG7.p3d";
        ammo = "BDE_RPG7_Shot_PG7";
    };

    class BDE_Ammo_PG7R : BDE_Ammo_OG7
    {
        displayName = "PG-7VR Rocket";
        descriptionShort = "The PG-7VR is a 105mm, fin-stabilized, Tandem-Shaped-Charge (TSC) High-Explosive Anti-Tank (HEAT) rocket designed specifically for use with the RPG-7V launcher.";
        model = "BDE_RPG7\models\RPG7_PG7R.p3d";
        ammo = "BDE_RPG7_Shot_PG7R";
    };
};

// Register cartridge identities with the engine's ammo serialization API.
class CfgAmmoTypes
{
    class AType_BDE_RPG7_Shot_OG7
    {
        name = "BDE_RPG7_Shot_OG7";
    };

    class AType_BDE_RPG7_Shot_PG7
    {
        name = "BDE_RPG7_Shot_PG7";
    };

    class AType_BDE_RPG7_Shot_PG7R
    {
        name = "BDE_RPG7_Shot_PG7R";
    };
};

class CfgAmmo
{
    class DefaultAmmo;
    class Bullet_40mm_Explosive;
    class Explosion_40mm_Ammo;

    // Invisible, harmless firing tokens allow vanilla chamber/FSM handling to run.
    // Only the server-created flight entity applies the rocket blast damage.
    class BDE_RPG7_Shot_OG7 : Bullet_40mm_Explosive
    {
        model = "\dz\weapons\projectiles\tracer_40mm_grenade.p3d";
        proxyShape = "";
        casing = "";
        round = "";
        spawnPileType = "BDE_Ammo_OG7";
        initSpeed = 1;
        typicalSpeed = 1;
        timeToLive = 0.001;
        tracerScale = 0;
        hit = 0;
        indirectHit = 0;
        indirectHitRange = 0;
        explosive = 0;
        caliber = 0;
        soundHit[] =
        {
            "", 0, 1
        };
        soundSetExplosion[] = {};

        class DamageApplied
        {
            type = "Projectile";
            bleedThreshold = 0;

            class Health
            {
                damage = 0;
            };

            class Blood
            {
                damage = 0;
            };

            class Shock
            {
                damage = 0;
            };
        };
    };

    class BDE_RPG7_Shot_PG7 : BDE_RPG7_Shot_OG7
    {
        spawnPileType = "BDE_Ammo_PG7";
        proxyShape = "";
        round = "";
    };

    class BDE_RPG7_Shot_PG7R : BDE_RPG7_Shot_OG7
    {
        spawnPileType = "BDE_Ammo_PG7R";
        proxyShape = "";
        round = "";
    };

    // Direct-hit damage used only by the scripted BDE rocket entity.
    class BDE_RPG7_Direct_PG7 : DefaultAmmo
    {
        hit = 5000;
        indirectHit = 0;
        indirectHitRange = 0;
        explosive = 0;
        caliber = 8;
        deflecting = 0;

        class DamageApplied
        {
            type = "Projectile";
            dispersion = 0;
            bleedThreshold = 1;

            class Health
            {
                damage = 5000;
            };

            class Blood
            {
                damage = 5000;
            };

            class Shock
            {
                damage = 5000;
            };
        };
    };

    class BDE_RPG7_Direct_PG7R : BDE_RPG7_Direct_PG7
    {
        hit = 1000000;

        class DamageApplied
        {
            type = "Projectile";
            dispersion = 0;
            bleedThreshold = 1;

            class Health
            {
                damage = 1000000;
            };

            class Blood
            {
                damage = 1000000;
            };

            class Shock
            {
                damage = 1000000;
            };
        };
    };

    // OG-7: slightly stronger and wider than the vanilla 40 mm explosion.
    class BDE_RPG7_Blast_OG7 : Explosion_40mm_Ammo
    {
        indirectHit = 1;
        indirectHitRange = 6;
        indirectHitRangeMultiplier = 4;

        class DamageApplied
        {
            type = "FragGrenade";

            class Health
            {
                damage = 75;
            };

            class Blood
            {
                damage = 0;
            };

            class Shock
            {
                damage = 0;
            };
        };
    };

    // PG-7: very strong direct hit with a deliberately small blast radius.
    class BDE_RPG7_Blast_PG7 : Explosion_40mm_Ammo
    {
        indirectHit = 1;
        indirectHitRange = 2.5;
        indirectHitRangeMultiplier = 2;

        class DamageApplied
        {
            type = "FragGrenade";

            class Health
            {
                damage = 50;
            };

            class Blood
            {
                damage = 0;
            };

            class Shock
            {
                damage = 0;
            };
        };
    };

    // PG-7R: high direct damage respects normal damage callbacks; splash matches
    // the vanilla 40 mm grenade damage profile.
    class BDE_RPG7_Blast_PG7R : Explosion_40mm_Ammo
    {
    };
};

class CfgNonAIVehicles
{
    class ProxyAttachment;
    class FxRound;

    class BDE_FxRound_OG7 : FxRound
    {
        model = "BDE_RPG7\models\RPG7_OG7.p3d";
    };

    class BDE_FxRound_PG7 : FxRound
    {
        model = "BDE_RPG7\models\RPG7_PG7.p3d";
    };

    class BDE_FxRound_PG7R : FxRound
    {
        model = "BDE_RPG7\models\RPG7_PG7R.p3d";
    };

    class ProxyRPG7_Bipod : ProxyAttachment
    {
        scope = 2;
        inventorySlot = "BDE_RPG7_Bipod";
        model = "BDE_RPG7\models\RPG7_Bipod.p3d";
    };

    class ProxyRPG7_Sights : ProxyAttachment
    {
        scope = 2;
        inventorySlot = "BDE_RPG7_Sights";
        model = "BDE_RPG7\models\RPG7_Sights.p3d";
    };

    class ProxyRPG7_Optic : ProxyAttachment
    {
        scope = 2;
        inventorySlot = "weaponOptics";
        model = "BDE_RPG7\models\RPG7_Optic.p3d";
    };
    class ProxyM72A7_LAW_Parts : ProxyAttachment
    {
        scope = 2;
        inventorySlot = "BDE_LAW_Parts";
        model = "BDE_RPG7\models\LAW\M72A7_LAW_Parts.p3d";
        class AnimationSources
        {
            class safety_slide
            {
                source = "user";
                initPhase = 0;
                animPeriod = 0.01;
            };
            class tube_extend
            {
                source = "user";
                initPhase = 0;
                animPeriod = 0.01;
            };
            class tube_cap_deploy
            {
                source = "user";
                initPhase = 0;
                animPeriod = 0.01;
            };
            class front_sight_deploy
            {
                source = "user";
                initPhase = 0;
                animPeriod = 0.01;
            };
            class rear_sight_deploy
            {
                source = "user";
                initPhase = 0;
                animPeriod = 0.01;
            };
            class sight_cover_hide
            {
                source = "user";
                initPhase = 0;
                animPeriod = 0.01;
            };
            class rocket_hide
            {
                source = "user";
                initPhase = 0;
                animPeriod = 0.01;
            };
        };
    };

};
