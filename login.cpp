#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
using namespace std;
// Fonction pour obtenir la variable d'envirenement 
string get_env_var(const string &key) {
    char *val = getenv(key.c_str());
    return val == nullptr ? string("") : string(val);
}

// Fonction pour extraire les valeurs des paramètres de la chaîne de requête
void parse_query_string(const string &query_string, string &username, string &password) {
    size_t pos_username = query_string.find("username=");
    size_t pos_password = query_string.find("password=");
    if (pos_username != string::npos) {
        username = query_string.substr(pos_username + 9, query_string.find("&", pos_username) - (pos_username + 9));
    }

    if (pos_password != string::npos) {
        password = query_string.substr(pos_password + 9);
}
}
bool fileUser(const string username, string password , string filename){
    string stor_user, stor_pass;
    ifstream file(filename);
    if (!file.is_open()){
        cout << "erreur de l'overture du fichier " << endl;
        exit(1);
    }
    while (file >> stor_user >> stor_pass){
        if(username==stor_user && password==stor_pass){
            return true;
        }
    }
    return false;
}
int main() {
    // En-têtes CGI
    cout << "Content-type: text/html\n\n";
 // Récupération de la chaîne de requête (query string) depuis l'environnement
    string query_string = get_env_var("QUERY_STRING");
    string username, password;
    parse_query_string(query_string, username, password);

    if (fileUser(username,password,"dataUser.txt")) {
        cout << "<h1>Bienvenue, " << username << "!</h1>";
    } else {
        cout << "<html><head>";
        cout << "<meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
        cout << " <link rel='stylesheet' href='style.css'><title>Document</title>";
        cout << "</head><body>";
        cout << "<div class='a'>";
        cout << "<h1>Site1</h1>";
        cout << "<form action='login.cgi' method='get'>";
        cout << "<input type='text' name='username' placeholder='username' value='" << username <<"' required>";
        cout << "<input type='password' name='password' placeholder='password' value='" << password <<"' required>";
        cout << "<button type='submit'>connection</button>";
        cout << "</form>";
        cout << "<a href='inscription.html'>inscription ?</a>";
        cout << "</div>";
        cout << "</body></html>";
    }

    return 0;
}
