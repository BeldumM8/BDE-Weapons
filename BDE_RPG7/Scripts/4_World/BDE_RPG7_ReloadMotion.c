// Generated from vanilla RPG7 ANM rotations and DayZ master-rig joint offsets.
// Distances are metres; frames are 30 FPS. Regrips deliberately hold the rocket.
class BDE_RPG7_ReloadMotion
{
    static void LoadGrip(out vector tm[4])
    {
        tm[0] = "-0.140545792 -0.958169799 -0.249314092";
        tm[1] = "-0.084240491 0.262473390 -0.961255044";
        tm[2] = "0.986483867 -0.114098009 -0.117606225";
        tm[3] = "-0.210559115 -0.563668630 -0.087067710";
    }

    static void FirstGrip(out vector tm[4])
    {
        tm[0] = "-0.289772188 -0.952427279 -0.094415868";
        tm[1] = "0.239751094 0.023269639 -0.970555478";
        tm[2] = "0.926580537 -0.303876293 0.221602588";
        tm[3] = "-0.373448027 -0.701238548 -0.033789964";
    }

    static void RegripBasis(out vector tm[4])
    {
        tm[0] = "0.583551733 0.317153655 -0.747583396";
        tm[1] = "-0.808982610 0.146761058 -0.569217295";
        tm[2] = "-0.070813216 0.936949706 0.342214461";
        tm[3] = "0.206020868 0.544385013 -0.314904658";
    }

    static void UnloadGrip(out vector tm[4])
    {
        tm[0] = "-0.344608994 -0.934437196 -0.089843014";
        tm[1] = "-0.552959035 0.279396518 -0.784967446";
        tm[2] = "0.758604605 -0.220827336 -0.612988043";
        tm[3] = "-0.317741288 -0.613810467 0.085798627";
    }

    protected static ref array<float> s_LoadFirst =
    {
        0.423339581,
        0.391673291,
        0.340022407,
        0.271005592,
        0.198529673,
        0.139200337,
        0.108828988,
        0.105617292
    };

    protected static ref array<float> s_LoadFinal =
    {
        0.105617292,
        0.072145490,
        0.029588542,
        0.002423980,
        0.000000000
    };

    protected static ref array<float> s_UnloadFirst =
    {
        0.000000000,
        0.002310822,
        0.002220878,
        0.001902321,
        0.001395972,
        0.000000000,
        0.032018993,
        0.135105454,
        0.194017442
    };

    protected static ref array<float> s_UnloadFinal =
    {
        0.194017442,
        0.201123637,
        0.225700987,
        0.268119940,
        0.323176161,
        0.375922387,
        0.421873278,
        0.468147889,
        0.513117029,
        0.543062534,
        0.563916411,
        0.581468049
    };

    static float Sample(array<float> values, float frame, int start)
    {
        float position = Math.Clamp(frame - start, 0, values.Count() - 1);
        int index = Math.Floor(position);
        if (index >= values.Count() - 1)
            return values[values.Count() - 1];
        return Math.Lerp(values[index], values[index + 1], position - index);
    }

    static float Slide(int mode, float frame)
    {
        if (mode == 1)
        {
            if (frame < 92.0)
                return Sample(s_LoadFirst, frame, 85);
            return Sample(s_LoadFinal, frame, 113);
        }
        if (frame < 34.0)
            return Sample(s_UnloadFirst, frame, 26);
        return Sample(s_UnloadFinal, frame, 49);
    }

    static void Grip(int mode, float frame, vector muzzle, out vector tm[4])
    {
        float distance;
        if (mode == 2)
        {
            UnloadGrip(tm);
            distance = Slide(2, 60);
        }
        else
        {
            if (frame < 34.0)
                FirstGrip(tm);
            else
                LoadGrip(tm);
            distance = Slide(1, 85);
        }
        vector position = muzzle + Vector(-distance, 0, 0);
        tm[3] = position.Multiply4(tm);
    }

    static void Regrip(vector muzzle, out vector tm[4])
    {
        RegripBasis(tm);
        vector position = muzzle + Vector(-Slide(1, 85), 0, 0);
        tm[3] = position.Multiply4(tm);
    }
}
