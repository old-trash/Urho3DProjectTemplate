using System.IO;
using System.Text.RegularExpressions;


class EmptyProject
{
    const string projectName = "Program";

    static void Main(string[] args)
    {
        string text = File.ReadAllText("01_HelloWorld.vcxproj");

        text = text.Replace("<ProjectName>01_HelloWorld</ProjectName>", "<ProjectName>" + projectName + "</ProjectName>");

        Regex regex = new Regex(@"  <ItemGroup>(.|\r\n)+?</ItemGroup>\r\n");
        text = regex.Replace(text, "");

        regex = new Regex(@"<AdditionalIncludeDirectories>(.+?)\\include");
        Match match = regex.Match(text);
        string path = match.Result("$1");
        text = text.Replace(@"..\..\..", path);

        regex = new Regex(@"<ImportLibrary>.+?/Samples/01_HelloWorld/(.+?)/.+?lib</ImportLibrary>");
        text = regex.Replace(text, "<ImportLibrary>$1/" + projectName + ".lib</ImportLibrary>");

        regex = new Regex(@"<ProgramDataBaseFile>.+?</ProgramDataBaseFile>");
        text = regex.Replace(text, "<ProgramDataBaseFile>../Result/" + projectName + ".pdb</ProgramDataBaseFile>");

        regex = new Regex(@"(<OutDir.+?>).+?</OutDir>");
        text = regex.Replace(text, "$1../Result/</OutDir>");

        regex = new Regex(@"(<TargetName.+?>).+?</TargetName>");
        text = regex.Replace(text, "$1" + projectName + "</TargetName>");

        regex = new Regex(@"<IntDir(.+?)>01_HelloWorld\.dir\\(.+?)</IntDir>");
        text = regex.Replace(text, "<IntDir$1>$2</IntDir>");

        File.WriteAllText(projectName + ".vcxproj", text);
    }
}
