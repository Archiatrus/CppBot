#include "sc2api/sc2_api.h"

#include "CppBot.h"
#include "LadderInterface.h"

int main(int argc, char* argv[])
{
        RunBot(argc, argv, new CppBot(), sc2::Race::Zerg);
        std::cout << "Cpp will close now." << std::endl;
	return 0;
}
