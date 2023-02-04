#include <fstream>
#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

//since songs in the osu sub-folders are usually called just audio, we get their names from the subfolder name
string get_songName(fs::path p)
{
    string tmp = "";
    string s = p.string();
    int i;
    for (i = s.length(); s[i] != '\\'; i--);
    for (--i; s[i] != '\\'; i--) tmp += s[i];
    string name = "";
    for (int k = tmp.length()-1; !isspace(tmp[k]); k--) tmp.pop_back();
    for (int j = tmp.length()-2; j >= 0; j--) name += tmp[j];
    return name;
}

int main()
{
    string osu_path("D:/Games/osu!"); //path where your game is installed 
    string songs_path("D:/Songs"); //path where the program will put the songs

    //iterates through all files in the osu beatmap folder
    for (auto& p : fs::recursive_directory_iterator(osu_path+"/Songs"))
    {
        //if the file is an mp3 format it's a song we want to extract
        if (p.path().extension() == ".mp3")
        {
            cout << "now copying " << p.path().string() << '\n';
            fs::path directory = songs_path + "/" + get_songName(p) + ".mp3";
            //if there are more songs with the same name they *should* get copied only once
            fs::copy_file(p.path(), directory, fs::copy_options::skip_existing); 
        }
            
    }
    cout << "Finished\n";
    return 0;
}