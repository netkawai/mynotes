In the beginning, Windows NT API was created in mind of nomenclature of the original Windows 16bit. 
However at the time, Unicode was about standarized but UTF-8 was not existed. So Microsoft define two APIs for one function with A and W.

The function with W has argument w_char (16bit), function with A has char (7bit).

Windows NT envolved in Windows 2000 with the integration of Windows 9x line. All APIs are integrated which eventually call in Win32 API.
At the time, Windows NT equals Windows 32bit version. Even 64it version Windows 7 came out, but most API manner or rules did not change.

From Windows 8, Microsoft introduced Windows Runtime and Microsoft Store. Those are analogy of what smartphone platform appeared late 2000s.
Basically the app runs on App Contains (the evolution of APP-V - Office app) with new App package format and provide mechanism to install without Admin (not Program Files),
and Settings can control certain aspect such as the local file access, the Internet, or some resources. Microsoft Store App.

However, those mechanims was introudced complete in different layer as a new COMs (other than Direct Runtime) due to the purpose or goal of this mechnism,
those two world are isolated, originally if the developer want to create Microsoft Store App, they have create a completely whole stuff.


Unlike iPhone or Android, those completely new device or new platform, Microsoft could not compete those software platform and hardware rapid revolution.
Microsoft failed to grab smartphone platform, the original intention of Windows Runtime and Store became garbage.

However, Microsoft did not expand the already lagacy component such as WPF/Winform. Instead of that, since Microsoft focused on Azure with Linux, abandon the original ASP.NET which
are tiely integrated with Windows Server, they de-culatered (de-coupled) .NET Platform.

And for Microsoft, App Container is useful in a certain situation, yes, historically, most App is expected into Program File in classic installer without any limitation except ACL,
However, if they can split new UIs (UI mechanism), App Container(Publish), and make Win32(original .NET Framework API) can communicate to them. Natually, some developers start to think,
Windows does not need ligid App framework, rather developers need them as components to pick by developers.

Now, Windows support three major executable way.
1. The single EXE (no package ID): Most traditional load PE file as execute in a process) -> More: Run as Administrator, Open File Location. (No App Settings, Share)
2. Packaged EXE with UWP conformant (i.e. UWP app, use only UWP api to support multiple type device on Windows/Microsoft Store,but dead) -> More: App Settings, Share, (No Run as Admnistorator)
3. Packaged EXE with Tranditional Win32/.NET App -> More: App Settings, Run as Administrator, Share
4. Packaged EXE with Windows App with Runtime Windows App Runtime. -> More: App Settings, Run as Administrator, Share

3 and 4 are still packaged, but only Windows 10 (1904) or Later, not necessary for Micorosft Store. It can be elevated. 
In default the EXE/App can access all resources on Windows. They still call desktop app (meh) 

Windows App SDK is not an open-source project, rather to open new UIs (UI mechanism) of WinRT to open up to the single Exe(traditinal EXE).
WPF/Winform in .NET are now MIT, it means, Microsoft will not add any new UI components (only improve perfomance and compatibility)

As of 2021-12-20, Microsoft does not have any killer Store App(MSIX package APP)s, even Desktop Office are single EXE due to compatibility and plugin. basically smartphone app will not have plugin/add-on nor  non-connected environment

Windows 10 Mobile is dead, Ad Monetization platform is dead, Cortana is dead.. 