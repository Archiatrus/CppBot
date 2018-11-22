#pragma once

#include "sc2api/sc2_api.h"
#include "sc2lib/sc2_lib.h"
#include "sc2utils/sc2_manage_process.h"
#include "sc2utils/sc2_arg_parser.h"

struct ConnectionOptions
{
	int32_t GamePort;
	int32_t StartPort;
	std::string ServerAddress;
	std::string OpponentId;
};

static void ParseArguments(int argc, char *argv[], ConnectionOptions &connect_options)
{
	sc2::ArgParser arg_parser(argv[0]);
	arg_parser.AddOptions({
		{ "-g", "--GamePort", "Port of client to connect to", false },
		{ "-o", "--StartPort", "Starting server port", false },
		{ "-l", "--LadderServer", "Ladder server address", false },
		{ "-i", "--OpponentId", "Id of the opponent", false }
		});
	arg_parser.Parse(argc, argv);

	std::string GamePortStr;
	if (arg_parser.Get("GamePort", GamePortStr)) {
		connect_options.GamePort = atoi(GamePortStr.c_str());
	}

	std::string StartPortStr;
	if (arg_parser.Get("StartPort", StartPortStr)) {
		connect_options.StartPort = atoi(StartPortStr.c_str());
	}
	
	arg_parser.Get("LadderServer", connect_options.ServerAddress);
	
	arg_parser.Get("OpponentId", connect_options.OpponentId);
}

static void RunBot(int argc, char *argv[], sc2::Agent *Agent,sc2::Race race)
{
	ConnectionOptions Options;
	ParseArguments(argc, argv, Options);

	sc2::Coordinator coordinator;

	// Add the custom bot, it will control the players.
	coordinator.SetParticipants({CreateParticipant(race, Agent)});

	// Start the game.

	std::cout << "Connecting to port " << Options.GamePort << std::endl;
	coordinator.SetTimeoutMS(30000);
	coordinator.Connect(Options.GamePort);
	coordinator.SetupPorts(2, Options.StartPort, false);
	// Step forward the game simulation.
	if (!coordinator.JoinGame())
	{
		std::cout << "Join Game failed for CppBot!" << std::endl;
		return;
	}
	std::cout << " Successfully joined game" << std::endl;
	while (coordinator.Update()) {
	}
	for(const auto& result : Agent->Observation()->GetResults())
	{
		if (result.player_id == Agent->Observation()->GetPlayerID())
		{
			std::cout << result.result << std::endl;
		}
	}
}
