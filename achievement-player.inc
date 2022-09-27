#define Player_GiveAchievementProgress(%0,%1,%2) Player_SetAchievementProgress(%0, %1, Player_GetAchievementProgress(%0, %1) + %2)

static enum E_PLAYER_ACHIEVEMENT_DATA {
  bool: E_PLAYER_ACHIEVEMENT_DATA_STATE,
  E_PLAYER_ACHIEVEMENT_DATA_PROG
};

static gPlayerAchievementData[MAX_PLAYERS][MAX_ACHIEVEMENTS][E_PLAYER_ACHIEVEMENT_DATA];

forward OnPlayerProgressAchievement(playerid, Achievement: id, progress);
forward OnPlayerUnlockAchievement(playerid, Achievement: id);

DEFINE_HOOK_REPLACEMENT(Achievement, Achv);

#define ALS_DO_PlayerProgressAchievement<%0> %0<PlayerProgressAchievement, ddd>(playerid, Achievement: id, progress)
#define ALS_DO_PlayerUnlockAchievement<%0> %0<PlayerUnlockAchievement, dd>(playerid, Achievement: id)

forward Player_SetAchievementProgress(playerid, Achievement: id, progress);
forward Player_GetAchievementProgress(playerid, Achievement: id);
forward bool: Player_IsUnlockedAchievement(playerid, Achievement: id);

stock Player_SetAchievementProgress(playerid, Achievement: id, progress) {
  if (!IsPlayerConnected(playerid)) {
    return 0;
  }

  if (!Achievement_IsValid(id)) {
    return -1;
  }

  if (Player_IsUnlockedAchievement(playerid, id)) {
    return -2;
  }

  new requirement = Achievement_GetRequirement(id);

  gPlayerAchievementData[playerid][_: id][E_PLAYER_ACHIEVEMENT_DATA_PROG] = (progress = clamp(progress, 0, requirement));

  call OnPlayerProgressAchievement(playerid, _: id, progress);

  if (progress == requirement) {
    gPlayerAchievementData[playerid][_: id][E_PLAYER_ACHIEVEMENT_DATA_STATE] = true;

    call OnPlayerUnlockAchievement(playerid, _: id);
  }
  return 1;
}

stock Player_GetAchievementProgress(playerid, Achievement: id) {
  return !(IsPlayerConnected(playerid) && Achievement_IsValid(id)) ? 0 : gPlayerAchievementData[playerid][_: id][E_PLAYER_ACHIEVEMENT_DATA_PROG];
}

stock bool: Player_IsUnlockedAchievement(playerid, Achievement: id) {
  return (IsPlayerConnected(playerid) && Achievement_IsValid(id)) && gPlayerAchievementData[playerid][_: id][E_PLAYER_ACHIEVEMENT_DATA_STATE];
}
