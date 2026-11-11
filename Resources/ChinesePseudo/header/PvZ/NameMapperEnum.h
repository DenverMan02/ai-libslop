#ifndef __PlantsVersusZombies2__PlantNameMapper_Enum__
#define __PlantsVersusZombies2__PlantNameMapper_Enum__

// const int material id
const int id_mat_coin_fire = 23001;
const int id_mat_coin_ice = 23002;
const int id_mat_evolution_fireflower = 23003;
const int id_mat_medal = 23004;
const int id_mat_redpacket_s = 23005;
const int id_mat_redpacket_b = 23006;
const int id_mat_nutrient_0 = 23007;
const int id_mat_nutrient_1 = 23008;
const int id_mat_nutrient_2 = 23009;
const int id_mat_nutrient_3 = 23010;
const int id_mat_nutrient_4 = 23011;
const int id_mat_redpacket_gold = 23012;
const int id_mat_gachakey_rare = 23015;
const int id_mat_gachakey_rare_multi = 23016;
const int id_mat_national_medal = 23017;
const int id_mat_national_currency = 23018;
const int id_mat_miniGame_currency = 23235;
const int id_mat_springFestival_currency = 23120;
const int id_mat_chrismas_medal = 23021;
const int id_mat_chrismas_currency = 23022;
const int id_mat_new_redpacket = 23071;
const int id_mat_festival_currency = 23024;
const int id_mat_new_dumpling = 23026;
const int id_steam_GemHammer = 23027;
const int id_mat_Gem = 3008;
const int id_coin_gold = 4013;
const int id_mat_ZMatch_ticket = 23028;
const int id_mat_ZMatch_challenges = 52282;
const int id_mat_BossRush_crystal = 23035;
const int id_mat_collect_coin_a = 23030;
const int id_mat_collect_coin_b = 23031;
const int id_mat_collect_coin_c = 23032;
const int id_mat_collect_coin_d = 23033;
const int id_mat_collect_coin_e = 23034;
const int id_mat_limitlottery_crystal = 23036;
const int id_mat_limitlottery_cup = 23037;
const int id_mat_2018NewYear_currency = 23045;
const int id_mat_BossRush_crystal_blue = 23258;
const int id_mat_plant_levelup_book = 23046;
const int id_mat_renaissance_challenge_statue = 23267;//复兴挑战Levelofday
const int id_mat_renaissance_challenge_statue_1 = 23259;//复兴挑战Levelofday1
const int id_mat_limitgroupbuy_ticket = 3010;
const int id_mat_worldcup_coin = 23061;
const int id_mat_richman_coin = 23091;
const int id_mat_space_time_crystal = 23094;
const int id_mat_space_time_dust = 23095;
const int id_mat_rift_coin = 23093;
const int id_mat_mystery_crystal = 23097;
const int id_mat_secret_gacha_ticket = 23098;
const int id_mat_fireworks = 23275;//舞狮来袭、圣诞献礼、踏青游春
const int id_mat_redpacket_ticket = 23242;
const int id_mat_callofwish_ticket = 23111;
const int id_mat_artifact_vial = 23112;
const int id_mat_artifact_cube = 23113;
const int id_mat_pvz1mode_coin = 23400;
const int id_mat_pvz1mode_coin_hard = 23401;
const int id_mat_customlevel_play_coin = 23402;
const int id_mat_customlevel_create_coin = 23403;
const int id_mat_festival_golden_egg_hammer = 23249;//砸金蛋
const int id_mat_penny_classroom_coin = 23405;
const int id_mat_general_plant_chips = 23226;
const int id_mat_universal_plant_chips = 23225;
const int id_mat_limited_summon_ticket = 23233;
const int id_mat_carnival_ticket = 23238;
const int id_mat_gene_factor = 23140;
const int id_mat_univeral_gene_sequence = 23141;
const int id_mat_new_pvp_purple_gold_coin = 23243;
const int id_mat_cornucopia_ticket = 23281;//聚宝盆幸运金币
const int id_mat_cornucopia_emblem = 23282;//聚宝盆兑换徽章
const int id_mat_wishing_coin = 23276; //许愿币
const int id_mat_Invitation_coin = 23262;
const int id_mat_party_assist_ticket = 23283;// 助力活动券
const int id_mat_artifact_bless_normal = 23123; //普通祝福券
const int id_mat_artifact_bless_advance = 23124; //高级祝福券
const int id_mat_dave_kitchen_ingredients_a = 23270; //戴夫厨房食材 玉米
const int id_mat_dave_kitchen_ingredients_b = 23271; //戴夫厨房食材 水
const int id_mat_dave_kitchen_ingredients_c = 23272; //戴夫厨房食材 蔬菜
const int id_mat_dave_kitchen_ingredients_d = 23273; //戴夫厨房食材 肉
const int id_mat_dragon_treasure_crystal = 23278;//龙之宝库 龙晶
const int id_mat_dragon_treasure_integral = 23279;//龙之宝库 积分

// TODO: every new items or modify item id , should add here
// items for bag
const int BagItemIDs[] = {
    id_mat_nutrient_4, //  MATERIAL_UI_JUMP_PLANT
    id_mat_nutrient_3, //  MATERIAL_UI_JUMP_PLANT
    id_mat_nutrient_2, //  MATERIAL_UI_JUMP_PLANT
    id_mat_nutrient_1, //  MATERIAL_UI_JUMP_PLANT
    id_mat_nutrient_0, //  MATERIAL_UI_JUMP_PLANT
    id_mat_plant_levelup_book, //  MATERIAL_UI_JUMP_PLANT
    id_mat_space_time_crystal, //  MATERIAL_UI_JUMP_ACCESSORY
    id_mat_space_time_dust, //  MATERIAL_UI_JUMP_ACCESSORY
    id_mat_ZMatch_ticket, //  Activity_Joust
    id_mat_rift_coin, //  Activity_Rift
    id_mat_secret_gacha_ticket, //  Activity_SecretGacha
    id_mat_limitlottery_crystal, //  Activity_LimitLottery
    id_mat_limitlottery_cup, //  Activity_LimitLottery
    id_mat_richman_coin, //  Activity_RichMan
    id_mat_renaissance_challenge_statue,// clear every version Activity_National_LevelOfDay_Entrance
//    id_mat_BossRush_crystal_blue,// clear every version Activity_BossChallengeMedalLottery
    id_mat_artifact_vial,// MATERIAL_UI_JUMP_ARTIFACT
    id_mat_artifact_cube,// MATERIAL_UI_JUMP_ARTIFACT
    id_mat_callofwish_ticket,// Activity_CallofWish
    id_mat_pvz1mode_coin,// Activity_PVZ1_Mode
    id_mat_pvz1mode_coin_hard,// Activity_PVZ1_Mode
    id_mat_general_plant_chips,
    id_mat_universal_plant_chips,
    id_mat_limited_summon_ticket,// Activity_LimitedSummon
    id_mat_carnival_ticket,
    id_mat_gene_factor,
    id_mat_univeral_gene_sequence,
    id_mat_new_pvp_purple_gold_coin,
    id_mat_cornucopia_ticket,// Activity_Cornucopia
    id_mat_cornucopia_emblem,
    id_mat_wishing_coin,
    id_mat_party_assist_ticket,// Activity_PartyAssist
    id_mat_artifact_bless_normal,
    id_mat_artifact_bless_advance
};

#endif
