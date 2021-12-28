namespace ViktorDev{
constexpr int gameQuanity = 3;
constexpr int gameNameLength = 50;
constexpr int connInfoLength = 50;
constexpr char connectionInfo[connInfoLength] = "dbname = serverdb";
constexpr char firstGameName[gameNameLength] = "game1";
constexpr char secondGameName[gameNameLength] = "game2";
constexpr char thirdGameName[gameNameLength] = "game3";
constexpr int firstGamePrice = 1000;
constexpr int secondGamePrice = 600;
constexpr int thirdGamePrice = 500;

constexpr int success = 0;
constexpr int errorWithFile = 1;
constexpr int errorSerializeMessage = 2;
constexpr int errorParseMessage = 3;
}