Unreal Engine 4 Setup
=====================

In order to use this library with Unreal engine you just need to add the Visual Studio
project to your UE4 Game Solution and ask it to build.

I recommend having the library directory in:

/YourSystem/Game/ThirdParty/libconjuring

The visual studio project is in ./projects/vs/


------------------------------------------------------

Once the library is being built correctly you should find all you need in

	- include/ 
	- Libraries/

In your game project build file (Game.Build.cs) you should add code so that the
game project links with the library project.

Here's an example of a working *.Build.cs file, customize to your own needs!


using UnrealBuildTool;
using System.IO;
using System;

public class Sandbox : ModuleRules
{

	public Sandbox(ReadOnlyTargetRules Target) : base(Target)
	{
        
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

        LoadConjuring(Target);
    }

	private string ModulePath
   	{
       get { return ModuleDirectory; }
   	}

   	private string ThirdPartyPath
  	{
   	    get { return Path.GetFullPath( Path.Combine( ModulePath, "../../ThirdParty/" ) ); }
   	}

    public bool LoadConjuring(ReadOnlyTargetRules Target)
    {
        bool isLibrarySupported = false;
        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            isLibrarySupported = true;
            string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";
            string LibrariesPath = Path.Combine(ThirdPartyPath, "libconjuring", "Libraries");
            
            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "Conjuring" + ".lib"));
        }
        if (isLibrarySupported)
        {
            // Include path
            PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "libconjuring", "include"));
        }
        return isLibrarySupported;
    }
}
