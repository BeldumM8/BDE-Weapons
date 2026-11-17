// Gameplay backblast: server-only, once per successfully spawned rocket.
// Distances are measured from the launcher's rear memory point to target centres.
class BDE_RPG7_BackblastDamage
{
    static const float RANGE = 20.0;
    static const float HALF_ANGLE = 35.0;
    static const float ROOM_SCAN = 12.0;

    static bool Living(EntityAI entity)
    {
        if (!entity || !entity.IsAlive())
        {
            return false;
        }
#ifdef EXPANSIONMODAI
        if (eAIBase.Cast(entity))
        {
            return true;
        }
#endif
        return entity.IsMan() || entity.IsAnimal() || entity.IsZombie();
    }

    static void ExcludeHierarchy(EntityAI entity, array<Object> excluded)
    {
        if (!entity)
        {
            return;
        }
        excluded.Insert(entity);
        array<EntityAI> children = new array<EntityAI>();
        entity.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, children);
        foreach (EntityAI child : children)
        {
            excluded.Insert(child);
        }
    }

    // Return nearest solid contact, excluding creatures and carried equipment.
    static float Clearance(vector start, vector direction, float length, array<Object> excluded, out bool buildingHit)
    {
        buildingHit = false;
        RaycastRVParams ray = new RaycastRVParams(start, start + direction * length, null, 0.01);
        ray.type = ObjIntersectFire;
        ray.flags = CollisionFlags.ALLOBJECTS;
        array<ref RaycastRVResult> hits = new array<ref RaycastRVResult>();
        DayZPhysics.RaycastRVProxy(ray, hits, excluded);
        float nearest = length;
        foreach (RaycastRVResult hit : hits)
        {
            float distance = vector.Distance(start, hit.pos);
            if (distance < nearest)
            {
                nearest = distance;
                buildingHit = Building.Cast(hit.obj) != null || Building.Cast(hit.parent) != null;
            }
        }
        return nearest;
    }

    static bool Visible(vector start, vector end, array<Object> excluded)
    {
        vector delta = end - start;
        float length = delta.Length();
        if (length < 0.05)
        {
            return true;
        }
        bool buildingHit;
        return Clearance(start, delta.Normalized(), length, excluded, buildingHit) >= length - 0.05;
    }

    static void ConeDamage(float distance, float cosine, out float health, out float shock)
    {
        health = 0;
        shock = 0;
        float edge = Math.Cos(HALF_ANGLE * Math.DEG2RAD);
        if (distance >= RANGE || cosine < edge)
        {
            return;
        }
        float core = Math.Cos(7.0 * Math.DEG2RAD);
        float angular = 0.25 + 0.75 * Math.Clamp((cosine - edge) / (core - edge), 0, 1);
        if (distance < 5.0)
        {
            health = angular;
            shock = 4.0 * angular;
        }
        else if (distance < 7.0)
        {
            float nearFraction = (distance - 5.0) / 2.0;
            health = (0.90 - 0.18 * nearFraction) * angular;
            shock = (4.0 - 2.6 * nearFraction) * angular;
        }
        else
        {
            float fade = Math.Clamp((RANGE - distance) / (RANGE - 7.0), 0, 1);
            health = 0.72 * fade * fade * angular;
            shock = 1.4 * fade * fade * angular;
        }
    }

    static float RoomPressure(vector origin, array<Object> excluded)
    {
        bool roofIsBuilding;
        float roof = Clearance(origin, "0 1 0", 6.0, excluded, roofIsBuilding);
        if (!roofIsBuilding || roof >= 6.0)
        {
            return 0;
        }
        bool floorIsBuilding;
        float floorDistance = Clearance(origin, "0 -1 0", 4.0, excluded, floorIsBuilding);
        if (floorDistance >= 4.0)
        {
            return 0;
        }
        float distances[8];
        int walls = 0;
        for (int i = 0; i < 8; i++)
        {
            float angle = i * Math.PI / 4.0;
            bool wallIsBuilding;
            distances[i] = Clearance(origin, Vector(Math.Sin(angle), 0, Math.Cos(angle)), ROOM_SCAN, excluded, wallIsBuilding);
            if (wallIsBuilding && distances[i] < ROOM_SCAN)
            {
                walls++;
            }
        }
        // A roof alone (porch/canopy) must not count as a confined room.
        if (walls < 6)
        {
            return 0;
        }
        float width = distances[2] + distances[6];
        float depth = distances[0] + distances[4];
        float volume = Math.Max(4.0, width * depth * (roof + floorDistance));
        float enclosure = walls / 8.0;
        return Math.Clamp(60.0 / volume, 0.05, 1.0) * enclosure;
    }

    static void Apply(vector origin, vector rearward, EntityAI launcher, PlayerBase shooter, BDE_RPG7_Flight rocket)
    {
        if (!GetGame().IsServer() || !launcher || !rocket)
        {
            return;
        }
        rearward.Normalize();
        array<Object> objects = new array<Object>();
        GetGame().GetObjectsAtPosition3D(origin, RANGE + 3.0, objects, null);
        array<EntityAI> targets = new array<EntityAI>();
        array<Object> excluded = new array<Object>();
        ExcludeHierarchy(launcher, excluded);
        ExcludeHierarchy(shooter, excluded);
        excluded.Insert(rocket);
        if (Living(shooter))
        {
            targets.Insert(shooter);
        }
        foreach (Object object : objects)
        {
            EntityAI entity = EntityAI.Cast(object);
            if (Living(entity) && targets.Find(entity) < 0)
            {
                targets.Insert(entity);
                ExcludeHierarchy(entity, excluded);
            }
        }
        float pressure = RoomPressure(origin, excluded);
        foreach (EntityAI target : targets)
        {
            if (!target.GetAllowDamage() || rocket.BDEIsProtectedByNinjins(target))
            {
                continue;
            }
            vector centre = target.GetCenter();
            vector delta = centre - origin;
            float distance = delta.Length();
            if (distance >= RANGE || !Visible(origin, centre, excluded))
            {
                continue;
            }
            float health = 0;
            float shock = 0;
            if (target != shooter && distance > 0.001)
            {
                ConeDamage(distance, vector.Dot(delta.Normalized(), rearward), health, shock);
            }
            if (pressure > 0 && distance < ROOM_SCAN)
            {
                // Interior exposure combines with the direct cone, rather than
                // replacing it. Walls stop it; open doorways can transmit it.
                float roomFade = Math.Clamp(1.0 - distance / ROOM_SCAN, 0, 1);
                health += 0.8 * pressure * roomFade;
                shock += 1.5 * pressure * roomFade;
            }
            if (health <= 0 && shock <= 0)
            {
                continue;
            }
            float maxHealth = target.GetMaxHealth("", "Health");
            float maxShock = target.GetMaxHealth("", "Shock");
            if (maxHealth > 0)
            {
                target.SetHealth("", "Health", Math.Max(0, target.GetHealth("", "Health") - maxHealth * health));
            }
            if (target.IsAlive() && maxShock > 0)
            {
                target.SetHealth("", "Shock", Math.Max(0, target.GetHealth("", "Shock") - maxShock * shock));
            }
        }
    }
}
