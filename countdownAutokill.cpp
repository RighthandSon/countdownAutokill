/*
 * countdownAutokill
 *   Copyright (C) 2021 GEP
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "bzfsAPI.h"

class countdownAutokill : public bz_Plugin
{
public:
    virtual const char* Name();
    virtual void Init(const char* config);
    virtual void Cleanup();
    virtual void Event(bz_EventData* eventData);
};

BZ_PLUGIN(countdownAutokill)

const char* countdownAutokill::Name()
{
    return "countdownAutokill 0.2.3";
}

void countdownAutokill::Init(const char* config)
{
    Register(bz_eTickEvent);
    Register(bz_eAllowSpawn);

    bz_registerCustomBZDBBool("_allowCountdownAutokill", true, 0, true);
    bz_registerCustomBZDBBool("_allowCountdownNoSpawn", true, 0, true);
}

void countdownAutokill::Cleanup()
{
    Flush();
}

void countdownAutokill::Event(bz_EventData* eventData)
{
    switch (eventData->eventType)
    {
    case bz_eAllowSpawn:
    {
        bz_AllowSpawnData_V2* data = (bz_AllowSpawnData_V2*)eventData;
        if (bz_isCountDownInProgress() && bz_getBZDBBool("_allowCountdownNoSpawn"))
        {
            data->allow = false;
            data->kickPlayer = false;
            data->message = "You must wait until match has begun to spawn.";
            data->handled = true;
        }

    }
    break;
    case bz_eTickEvent:
    {
        if (bz_isCountDownInProgress() && bz_getBZDBBool("_allowCountdownAutokill"))
        {
            bz_APIIntList* players = bz_newIntList();
            bz_getPlayerIndexList(players);
            for (unsigned int x = 0; x < players->size(); x++)
            {
                bz_BasePlayerRecord* record = bz_getPlayerByIndex(players->get(x));
                if (record)
                {
                    if (record->spawned)
                        bz_killPlayer(record->playerID, false);
                    bz_freePlayerRecord(record);
                }
            }
            bz_deleteIntList(players);
        }

    }
    break;

    default:
        break;
    }
}
// Local Variables: ***
// mode: C++ ***
// tab-width: 4 ***
// c-basic-offset: 4 ***
// indent-tabs-mode: nil ***
// End: ***
// ex: shiftwidth=4 tabstop=4
