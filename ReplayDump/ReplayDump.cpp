// This contains the actual code for processing the replay and dumping the
// relevant information to a file.

#include "stdafx.h"
#include "ReplayDump.h"

using namespace BWAPI;
using namespace std;

void BWAPIReplay::onStart() {
	// Note: We don't seem to have any sensible default working directory and
	// mapFileName() doesn't return any valid value, further it doesn't seeem to
	// handle using ~ for expansion.  Hence this ugly hardcode.
	out_file.open("E:\\Users\\Megan\\Replay.txt");
	out_file << "Map " << Broodwar->mapHeight() << " " << Broodwar->mapWidth() << endl;

	explorer = 0;
}

void BWAPIReplay::onEnd(bool isWinner) {
	out_file.close();
}

void BWAPIReplay::onFrame() {
	out_file << "Frame: " << Broodwar->getFrameCount() << endl;

	if (explorer == 0) {
		// First time around find the exploration unit.  This is very much a
		// quick hack to locate the worker of the first player.  This works
		// for the standard exploration maps but needs expanding if we try
		// anything more complicated.
		Unitset myUnits = Broodwar->getPlayers()[0]->getUnits();
		for (Unitset::iterator u = myUnits.begin(); u != myUnits.end(); u++) {
			if (!u->exists())
				continue;

			if (u->getType().isWorker()) {
				explorer = u->getID();
			}
		}
	}

	Unit u = Broodwar->getUnit(explorer);
	TilePosition p = u->getTilePosition();
	out_file << "Position: " << p.x << " " << p.y << endl;
}

void BWAPIReplay::onSendText(std::string text) {}

void BWAPIReplay::onReceiveText(BWAPI::Player player, std::string text) {}

void BWAPIReplay::onPlayerLeft(BWAPI::Player player) {}

void BWAPIReplay::onNukeDetect(BWAPI::Position target) {}

void BWAPIReplay::onUnitDiscover(BWAPI::Unit unit) {}

void BWAPIReplay::onUnitEvade(BWAPI::Unit unit) {}

void BWAPIReplay::onUnitShow(BWAPI::Unit unit) {}

void BWAPIReplay::onUnitHide(BWAPI::Unit unit) {}

void BWAPIReplay::onUnitCreate(BWAPI::Unit unit) {}

void BWAPIReplay::onUnitDestroy(BWAPI::Unit unit) {}

void BWAPIReplay::onUnitMorph(BWAPI::Unit unit) {}

void BWAPIReplay::onUnitRenegade(BWAPI::Unit unit) {}

void BWAPIReplay::onSaveGame(std::string gameName) {}

void BWAPIReplay::onUnitComplete(BWAPI::Unit unit) {}
