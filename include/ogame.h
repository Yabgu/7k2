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

// Filename	  : OGAME.H
// Description : Header file for Game class

#ifndef __OGAME_H
#define __OGAME_H

#include <win32_compat.h>

#ifndef __GAMEDEF_H
#include <gamedef.h>
#endif

#ifndef __OEND_CON_H
#include <oend_con.h>
#endif

#ifdef DEBUG
#include <olonglog.h>
#endif

//-------- Define game modes -----------//

enum
{
    GAME_PREGAME = 1,
    GAME_SINGLE_PLAYER, // game_mode is set once the player clicks an option on
                        // the screen, the game doesn't have to be actually
                        // running.
    GAME_TUTORIAL,
    GAME_TEST,
    GAME_MULTI_PLAYER,
    GAME_CAMPAIGN,
    GAME_ENCYCLOPEDIA,
    GAME_CREDITS,
    GAME_SCENARIO_EDITOR,
};

// ----- define constant -------//

#define MAX_WIN_CONDITION 8
#define MAX_LOSE_CONDITION 8

// -------- typedef ----------//

//--------- Define struct ColorRemapMethod ----------//

struct ColorRemapMethod
{
    int primary_color;
    int secondary_color;
};

//--------- Define struct ColorRemap ----------//

#pragma pack(1)
struct ColorRemap
{
  public:
    char main_color;
    char dummy;
    short main_color_w;
    short color_table[256];

  public:
    void set_remap_color(ColorRemapMethod *);
    void load(short *);
};
#pragma pack()

//----- define struct ScenInfo -------//

struct ScenInfo
{
    enum
    {
        SCEN_NAME_LEN = 80
    };

    char *file_name;
    char scen_name[SCEN_NAME_LEN + 1];
    char dir_id; // real path look from DIR_SCENARIO_PATH(dir_id)
    short goal_difficulty;
    short goal_score_bonus;
};

//-------- Define class Game -----------//

struct Location;
struct NewNationPara;
class File;
class Campaign;

#pragma pack(1)
class Game
{
  public:
    char init_flag;
    char started_flag;
    char game_mode;
    char game_has_ended; // whether game_end() has been called once already and
                         // the player is now just staying in the game to continue
                         // to play or observe

    //-------- victory conditions --------//

    char win_require_all_condition; // the player only wins when all conditions
                                    // are met

    int win_condition_count;
    int lose_condition_count;
    EndCondition win_condition[MAX_WIN_CONDITION];
    EndCondition lose_condition[MAX_LOSE_CONDITION];
    int win_deadline;

    //---------- game results ------------//

    int result_win_condition_id;
    int result_lose_condition_id;
    char result_win_condition_recno;
    char result_lose_condition_recno;
    char result_defeated;

    //-------- color remap info ----------//

    ColorRemap color_remap_array[MAX_COLOR_SCHEME + 1];

  private:
    Campaign *cur_campaign;
    static char *auto_load_file_name;

    // ------- newly added variable -------//
  public:
    int total_gem_stones;
    int max_ranking; // lobbied game
    WORD player_ranking[MAX_NATION];
    long generated_serial; // generated by serial_repository

  public:
    Game();
    ~Game();

    void init_remap_table();
    int init(int loadGameCall = 0);
    void deinit(int loadGameCall = 0);
    void deinit_all();

    void main_menu();
    void set_load_game_in_main_menu(char *); // game to load automatically in main_menu
    void clear_load_game_in_main_menu();     // game to load automatically in main_menu
    void in_game_menu();
    int in_game_option_menu();
    void game_end(int winNationRecno, int playerDestroyed = 0, int surrenderToNationRecno = 0, int retireFlag = 0);

    void main_loop_all(int isLoadedGame = 0);

    int is_campaign_mode()
    {
        return cur_campaign != 0;
    }
    Campaign *campaign()
    {
        return cur_campaign;
    }

    int select_run_scenario(int countScenarioOnly = 0);
    int select_scenario(int scenCount, ScenInfo *scenInfoArray);
    int run_scenario(ScenInfo *scenInfo);

    void demo_disp_ad_page();
    void demo_disp_logo();

    short *get_color_remap_table(int nationRecno, int selectedFlag);
    static void disp_gen_game_status(int addStep);

    void multi_player_menu(int lobbied, char *game_host);

    int is_edit_mode()
    {
        return game_mode == GAME_SCENARIO_EDITOR;
    }

    //----- victory condition functions -----//

    void reset_win_condition();
    void add_win_condition(int condId, int playerOnly, int p1 = 0, int p2 = 0, int yearLimit = 0);
    void del_win_condition(int);
    void add_lose_condition(int condId, int playerOnly, int p1 = 0, int p2 = 0, int yearLimit = 0);
    void del_lose_condition(int);
    void set_win_deadline();
    int update_condition_on_killed(long uniqueId); // check unit killed
    int update_condition_on_mobilize(int newUnitRecno,
                                     long uniqueId); // check unit re-mobilized
    int update_condition_site_taken(int siteRecno, int nationRecno);
    int update_condition_item_acquired(short itemId, int nationRecno);
    int is_unit_in_condition(long uniqueId);

    //------- file functions -------//

    int write_file(File *filePtr);
    int read_file(File *filePtr);

    //------- debugging log ----------//

#ifdef DEBUG
    static LongLog *debug_log;
#endif

  private:
    void disp_version();
    void run_main_menu_option(int);
    void single_player_menu();
    void scenario_editor_menu();

    void single_player_game(int);
    void multi_player_game(int lobbied, char *game_host);
    void load_mp_game(char *saveFileName, int lobbied, char *game_host);
    void view_encyclopedia();
    void view_credits();

    int input_box(const char *tell_string, char *name, int name_len);

    void run_campaign();
    int select_campaign_menu();
    void init_campaign(int campaignId);
    void deinit_campaign();
    int campaign_class_size(int campaignId);

    //------- multiplayer game functions -------//

    int mp_select_mode(char *saveGameName);
    int mp_get_leader_board();
    int mp_join_session(int session_id, char *player_name);
    void mp_close_session();
    int mp_select_service();
    int mp_select_session();
    int mp_select_option(NewNationPara *, int *);
    int mp_select_load_option(char *);

    // --------- scenario editor -------- //

    //	void			scenario_editor();
};
#pragma pack()

extern Game game;
extern char game_demo_mode, game_design_mode;

//-------------------------------------//

#endif
