// Presentation only. No cartridge, inventory, firing or projectile operations.
class BDE_RPG7_ReloadProp extends House
{
    override bool CanBeActionTarget()
    {
        return false;
    }
}

class BDE_RPG7_ReloadProp_OG7 extends BDE_RPG7_ReloadProp
{
}

class BDE_RPG7_ReloadProp_PG7 extends BDE_RPG7_ReloadProp
{
}

class BDE_RPG7_ReloadProp_PG7R extends BDE_RPG7_ReloadProp
{
}

class BDE_RPG7_ReloadVisual
{
    protected BDE_RPG7 m_Weapon;
    protected Object m_Prop;
    protected EntityAI m_SourceVisual;
    protected bool m_SourceWasVisible;
    protected int m_Mode;
    protected int m_Rocket;
    protected int m_IndexBone = -1;
    protected int m_PinkyBone = -1;
    protected int m_MiddleBone = -1;
    protected int m_TipBone = -1;
    protected int m_WristBone = -1;
    protected bool m_HaveCarryPose;
    protected bool m_HaveRegripPose;
    protected vector m_CarryPose[4];
    protected vector m_RegripPose[4];
    protected float m_Frame;
    protected bool m_Running;
    protected bool m_WasVisible;

    void BDE_RPG7_ReloadVisual(BDE_RPG7 weapon, int mode, int rocket, float frame)
    {
        m_Weapon = weapon;
        m_Mode = mode;
        m_Rocket = rocket;
        m_Frame = frame;
        m_Running = true;
        GetGame().GetUpdateQueue(CALL_CATEGORY_GAMEPLAY).Insert(Update);
    }

    void Stop()
    {
        m_Running = false;
        GetGame().GetUpdateQueue(CALL_CATEGORY_GAMEPLAY).Remove(Update);
        RestoreSourceVisual();
        if (m_Prop)
        {
            GetGame().ObjectDelete(m_Prop);
            m_Prop = null;
        }
    }

    void RestoreSourceVisual()
    {
        if (m_SourceVisual && m_SourceWasVisible)
            m_SourceVisual.SetFlags(EntityFlags.VISIBLE, false);
        m_SourceVisual = null;
    }

    bool Matches(int mode, int rocket)
    {
        return m_Running && mode == m_Mode && rocket == m_Rocket;
    }

    void CorrectFrame(float frame)
    {
        // Small network jitter must not replay a slide or restart a regrip.
        if (Math.AbsFloat(frame - m_Frame) > 6.0)
            m_Frame = Math.Max(m_Frame, frame);
    }

    int DisplayedRocket(int chamberRocket)
    {
        if (!m_Running)
            return chamberRocket;

        if (m_Mode == 1)
        {
            if (m_Frame >= 117.0)
                return m_Rocket;
            return 0;
        }

        if (m_Frame >= 26.0)
            return 0;
        return chamberRocket;
    }

    protected vector Cross(vector a, vector b)
    {
        return Vector(a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]);
    }

    protected bool HandPose(PlayerBase player, out vector tm[4])
    {
#ifdef DAYZ_1_30
        // Bone lookup uses -1 as its failure sentinel; other signed IDs are valid.
        if (m_IndexBone == -1)
#else
        if (m_IndexBone < 0)
#endif
        {
            m_IndexBone = player.GetBoneIndexByName("LeftHandIndex1");
            m_PinkyBone = player.GetBoneIndexByName("LeftHandPinky1");
            m_MiddleBone = player.GetBoneIndexByName("LeftHandMiddle1");
            m_TipBone = player.GetBoneIndexByName("LeftHandMiddle3");
            m_WristBone = player.GetBoneIndexByName("LeftHand");
        }
#ifdef DAYZ_1_30
        // Bone lookup uses -1 as its failure sentinel; other signed IDs are valid.
        if (m_IndexBone == -1 || m_PinkyBone == -1 || m_MiddleBone == -1 || m_TipBone == -1 || m_WristBone == -1)
#else
        if (m_IndexBone < 0 || m_PinkyBone < 0 || m_MiddleBone < 0 || m_TipBone < 0 || m_WristBone < 0)
#endif
            return false;

        vector index = player.GetBonePositionWS(m_IndexBone);
        vector pinky = player.GetBonePositionWS(m_PinkyBone);
        vector middle = player.GetBonePositionWS(m_MiddleBone);
        vector tip = player.GetBonePositionWS(m_TipBone);
        vector wrist = player.GetBonePositionWS(m_WristBone);

        // The clip grips with the thumb toward the booster. The warhead points
        // toward the little-finger side. Use positions, not bone-local axes.
        vector forward = pinky - index;
        if (forward.Normalize() < 0.001)
            return false;
        tm[0] = -forward;
        vector palm = middle - wrist;
        palm = palm - tm[0] * vector.Dot(palm, tm[0]);
        if (palm.Normalize() < 0.001)
            return false;
        tm[1] = palm;
        tm[2] = Cross(tm[0], tm[1]);
        tm[2].Normalize();

        // Longitudinal grip positions measured from the original animation.
        // Centre the shaft inside the curled fingers, not below the wrist.
        float grip = 0.08793;
        if (m_Mode == 2)
            grip = 0.16193;
        else if (m_Frame < 34.0)
            grip = -0.03350;
        vector centre = (middle + tip) * 0.5;
        tm[3] = centre - tm[0] * grip;
        return true;
    }

    protected void TubePose(vector weaponTM[4], vector muzzle, float frame, out vector tm[4])
    {
        vector localTM[4];
        Math3D.MatrixIdentity4(localTM);
        localTM[3] = muzzle + Vector(-BDE_RPG7_ReloadMotion.Slide(m_Mode, frame), 0, 0);
        Math3D.MatrixMultiply4(weaponTM, localTM, tm);
    }

    protected void BlendPose(vector start[4], vector finish[4], float amount, out vector result[4])
    {
        amount = Math.Clamp(amount, 0, 1);
        amount = amount * amount * (3.0 - 2.0 * amount);
        vector startRotation[3];
        vector finishRotation[3];
        vector rotation[3];
        for (int axis = 0; axis < 3; axis++)
        {
            startRotation[axis] = start[axis];
            finishRotation[axis] = finish[axis];
        }
        float first[4];
        float last[4];
        float blended[4];
        Math3D.MatrixToQuat(startRotation, first);
        Math3D.MatrixToQuat(finishRotation, last);
        float dot;
        for (int component = 0; component < 4; component++)
            dot += first[component] * last[component];
        if (dot < 0)
        {
            for (int sign = 0; sign < 4; sign++)
                last[sign] = -last[sign];
        }
        Math3D.QuatLerp(blended, first, last, amount);
        float length;
        for (int square = 0; square < 4; square++)
            length += blended[square] * blended[square];
        length = Math.Sqrt(length);
        for (int normal = 0; normal < 4; normal++)
            blended[normal] = blended[normal] / length;
        Math3D.QuatToMatrix(blended, rotation);
        for (int basis = 0; basis < 3; basis++)
            result[basis] = rotation[basis];
        result[3] = start[3] + (finish[3] - start[3]) * amount;
    }

    void Update(float timeslice)
    {
        if (!m_Running)
            return;

        if (!m_Weapon || m_Weapon.IsSetForDeletion())
        {
            Stop();
            return;
        }

        PlayerBase player = PlayerBase.Cast(m_Weapon.GetHierarchyRootPlayer());
        if (!player || !player.IsAlive() || player.IsUnconscious() || player.GetHumanInventory().GetEntityInHands() != m_Weapon)
        {
            Stop();
            m_Weapon.BDEUpdateVisuals();
            return;
        }

        // Vanilla temporarily reserves the real ammo in the left-hand slot.
        // Hide its render model locally so it cannot duplicate the moving prop.
        EntityAI source = player.GetInventory().FindAttachment(InventorySlots.LEFTHAND);
        if (source != m_SourceVisual)
        {
            RestoreSourceVisual();
            if (source && source.IsInherited(BDE_Ammo_OG7))
            {
                m_SourceVisual = source;
                m_SourceWasVisible = (source.GetFlags() & EntityFlags.VISIBLE) != 0;
            }
        }
        if (m_SourceVisual)
            m_SourceVisual.ClearFlags(EntityFlags.VISIBLE, false);

        m_Frame += timeslice * 30.0;
        float finish = 148.0;
        if (m_Mode == 2)
            finish = 115.0;
        if (m_Frame > finish + 3.0)
        {
            Stop();
            m_Weapon.BDEUpdateVisuals();
            return;
        }

        bool visible;
        if (m_Mode == 1)
            visible = m_Frame >= 29.0 && m_Frame < 117.0;
        else
            visible = m_Frame >= 26.0 && m_Frame < 92.0;

        if (visible && !m_Prop)
        {
            string type = "BDE_RPG7_ReloadProp_PG7";
            if (m_Rocket == 1)
                type = "BDE_RPG7_ReloadProp_OG7";
            else if (m_Rocket == 3)
                type = "BDE_RPG7_ReloadProp_PG7R";

            // Local object, no AI, no physics body. Never a flight entity.
            m_Prop = GetGame().CreateObject(type, m_Weapon.GetPosition(), true, false, false);
        }
        if (!visible && m_Prop)
        {
            GetGame().ObjectDelete(m_Prop);
            m_Prop = null;
        }

        if (m_Prop)
        {
            vector weaponTM[4];
            m_Weapon.GetRenderTransform(weaponTM);
            vector playerTM[4];
            player.GetRenderTransform(playerTM);
            vector result[4];
            vector handTM[4];
            vector tubeTM[4];
            vector heldTM[4];
            vector muzzle = m_Weapon.GetMemoryPointPos("usti hlavne");
            bool inTube = m_Mode == 1 && m_Frame >= 85.0;
            if (m_Mode == 2 && m_Frame <= 60.0)
                inTube = true;

            if (inTube)
            {
                TubePose(weaponTM, muzzle, m_Frame, result);
            }
            else
            {
                if (!HandPose(player, handTM))
                {
                    Stop();
                    m_Weapon.BDEUpdateVisuals();
                    return;
                }

                for (int axis = 0; axis < 4; axis++)
                    result[axis] = handTM[axis];

                if (m_Mode == 1)
                {
                    if (m_Frame < 34.0)
                    {
                        Math3D.MatrixInvMultiply4(playerTM, result, m_CarryPose);
                        m_HaveCarryPose = true;
                    }
                    else if (m_Frame < 49.0)
                    {
                        if (!m_HaveRegripPose)
                        {
                            if (m_HaveCarryPose)
                            {
                                for (int boneAxis = 0; boneAxis < 4; boneAxis++)
                                    m_RegripPose[boneAxis] = m_CarryPose[boneAxis];
                            }
                            else
                            {
                                Math3D.MatrixInvMultiply4(playerTM, handTM, m_RegripPose);
                            }
                            m_HaveRegripPose = true;
                        }
                        // During a regrip the rocket stays beside the player;
                        // it must not swing around with the independently moving RPG.
                        Math3D.MatrixMultiply4(playerTM, m_RegripPose, heldTM);
                        BlendPose(heldTM, handTM, (m_Frame - 41.0) / 8.0, result);
                    }
                    else if (m_Frame >= 65.0)
                    {
                        // Guide the booster onto the bore before the first
                        // insertion stroke; no hard hand-to-barrel snap.
                        TubePose(weaponTM, muzzle, 85.0, tubeTM);
                        BlendPose(handTM, tubeTM, (m_Frame - 65.0) / 20.0, result);
                    }
                }
                else if (m_Frame < 68.0)
                {
                    TubePose(weaponTM, muzzle, 60.0, tubeTM);
                    BlendPose(tubeTM, handTM, (m_Frame - 60.0) / 8.0, result);
                }
            }
            m_Prop.SetTransform(result);
        }

        // Handoff to the chamber selection on the same rendered frame.
        if (visible != m_WasVisible || m_Frame >= 117.0)
        {
            m_WasVisible = visible;
            m_Weapon.BDEUpdateVisuals();
        }
    }
}

class BDE_RPG7_Unload extends WeaponEjectBullet
{
    override void OnEntry(WeaponEventBase e)
    {
        BDE_RPG7 launcher = BDE_RPG7.Cast(m_weapon);
        launcher.BDEStartReloadPresentation(2, null);
        super.OnEntry(e);
    }

    override void OnExit(WeaponEventBase e)
    {
        super.OnExit(e);
        BDE_RPG7.Cast(m_weapon).BDEStopReloadPresentation();
    }

    override void OnAbort(WeaponEventBase e)
    {
        super.OnAbort(e);
        BDE_RPG7.Cast(m_weapon).BDEStopReloadPresentation();
    }
}
