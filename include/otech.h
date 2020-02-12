/*
 * Seven Kingdoms 2: The Fryhtan War
 *
 * Copyright 1999 Enlight Software Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

// Filename    : OTECH.H
// Description : enum type of tech

#ifndef __OTECH_H
#define __OTECH_H

#define MAX_RACE 12
// comply with GAMEDEF.H
// if both MAX_RACE are different, compiler shows error message

enum {
  TECH_CLASS_NULL = 0, // keep it before the first

  FIRST_TECH_CLASS_RESEARCH,
  TECH_CLASS_PRODUCTION = FIRST_TECH_CLASS_RESEARCH,
  TECH_CLASS_SPYING,
  TECH_CLASS_INFANTRY,
  TECH_CLASS_SPU_STRUCTURE,
  TECH_CLASS_SPU_BERSERKER,
  TECH_CLASS_WEAPON,
  TECH_CLASS_OFFENSIVE_STRUCTURE,
  LAST_TECH_CLASS_RESEARCH =
      TECH_CLASS_OFFENSIVE_STRUCTURE, // last researchable tech class

  TECH_CLASS_MEGA_WEAPON,

  FIRST_TECH_CLASS_FRYHTAN,
  TECH_CLASS_PLANT = FIRST_TECH_CLASS_FRYHTAN,
  TECH_CLASS_INSECT,
  TECH_CLASS_ANIMAL,
  TECH_CLASS_ALCHEMY,
  TECH_CLASS_FORTRESS,
  TECH_CLASS_INCUBATION,
  TECH_CLASS_MAGIC,
  LAST_TECH_CLASS_FRYHTAN = TECH_CLASS_MAGIC,

  TECH_CLASS_MAX, // keep it after the last tech class
  MAX_TECH_CLASS = TECH_CLASS_MAX - 1
};

enum {
  TECH_NULL = 0, // keep it before the first

  TECH_MINING,
  TECH_MANUFACTURING,
  TECH_WAR_MACHINE,
  TECH_FARMING,

  TECH_AGITATION,
  TECH_COUNTER_SPY,
  TECH_INFO_THEFT,
  TECH_BRIBE,
  TECH_ASSASSIN,
  TECH_STEAL_TECH,
  TECH_CAMOUFLAGE,
  TECH_INCIDENT,

  TECH_INFANTRY_CLOSE_COMBAT,
  TECH_INFANTRY_RANGE_COMBAT,
  TECH_INFANTRY_DEFENSE,

  TECH_SPU_STRUCTURE_FIRST, // see also TECH_SPU_STRUCTURE macro
  TECH_SPU_STRUCTURE_LAST = TECH_SPU_STRUCTURE_FIRST + MAX_RACE - 1,

  TECH_SPU_BERSERK_FIRST, // see also TECH_SPU_BERSERK macro
  TECH_SPU_BERSERK_LAST = TECH_SPU_BERSERK_FIRST + MAX_RACE - 1,

  TECH_CATAPULT,
  TECH_BALLISTA,
  TECH_CANNON,
  TECH_FLAMETHR,
  TECH_EXPCART,
  TECH_F_BALLISTA,

  TECH_MEGA_CANNON,
  TECH_MEGA_F_BALLISTA,
  TECH_MEGA_SAW,

  TECH_OFFENSIVE_STRUCTURE_1,
  TECH_OFFENSIVE_STRUCTURE_2,
  TECH_OFFENSIVE_STRUCTURE_3,
  TECH_OFFENSIVE_STRUCTURE_4,

  TECH_LISHORR,
  TECH_WILDE_LISHORR,
  TECH_CAMOUFLAGE_ABILITY,
  TECH_BEE,
  TECH_TERMITE,
  TECH_JAGUAR,
  TECH_GORILLA,
  TECH_RHINO,
  TECH_LIVE_TO_GOLD,
  TECH_GOLD_TO_LIVE,
  TECH_RAW_TO_LIVE,
  TECH_RAW_TO_GOLD,
  TECH_ALCHEMY_YIELD,
  TECH_FORTRESS,
  TECH_FORTRESS_CAMOUFLAGE,
  TECH_WEAPON_1,
  TECH_WEAPON_2,
  TECH_WEAPON_3,
  TECH_MAGIC_DAMAGE_BUILDING,
  TECH_MAGIC_FREEZE_UNIT,
  TECH_MAGIC_DAMAGE_AREA,
  TECH_MAGIC_TELEPORT,

  TECH_MAX, // keep it after the last tech
  MAX_TECH = TECH_MAX - 1
};

#define TECH_SPU_STRUCTURE(raceId) (TECH_SPU_STRUCTURE_FIRST - 1 + raceId)
#define TECH_SPU_BERSERK(raceId) (TECH_SPU_BERSERK_FIRST - 1 + raceId)

#endif