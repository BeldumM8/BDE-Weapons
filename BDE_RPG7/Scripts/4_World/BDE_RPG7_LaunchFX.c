class BDE_RPG7_LaunchFX
{
    static void Backblast(Object launcher)
    {
        if (!GetGame().IsClient() || !launcher || !launcher.MemoryPointExists("backblast"))
        {
            return;
        }
        vector transform[4];
        launcher.GetRenderTransform(transform);
        vector position = launcher.GetMemoryPointPos("backblast").Multiply4(transform);
        Particle puff = ParticleManager.GetInstance().PlayInWorld(ParticleList.BDE_RPG7_BACKBLAST, position);
        if (puff)
        {
            transform[3] = position;
            puff.SetTransform(transform);
        }
    }
}
