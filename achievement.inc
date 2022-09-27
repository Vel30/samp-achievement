#include <YSI_Core\y_utils>

#define MAX_ACHIEVEMENTS 16
#define MAX_ACHIEVEMENT_NAME 32
#define MAX_ACHIEVEMENT_DESCRIPTION 128

const Achievement: INVALID_ACHIEVEMENT_ID = Achievement: cellmin;

static enum E_ACHIEVEMENT_DATA {
  string: E_ACHIEVEMENT_DATA_NAME[MAX_ACHIEVEMENT_NAME + 1 char],
  E_ACHIEVEMENT_DATA_REQUIREMENT,
  string: E_ACHIEVEMENT_DATA_DESCRIPTION[MAX_ACHIEVEMENT_DESCRIPTION + 1 char]
};

static gAchievementData[MAX_ACHIEVEMENTS][E_ACHIEVEMENT_DATA],
  gAchievementPoolSize;

forward Achievement: Achievement_Define(const string: name[], requirement, const string: description[] = "");
forward bool: Achievement_IsValid(Achievement: id);
forward bool: Achievement_GetName(Achievement: id, string: name[], length = sizeof(name));
forward Achievement_GetRequirement(Achievement: id);
forward bool: Achievement_GetDescription(Achievement: id, string: description[], length = sizeof(description));
forward Achievement_GetPoolSize();

stock Achievement: Achievement_Define(const string: name[], requirement, const string: description[] = "") {
  if (gAchievementPoolSize == MAX_ACHIEVEMENTS) {
    return INVALID_ACHIEVEMENT_ID;
  }

  new id = gAchievementPoolSize;

  strpack(gAchievementData[id][E_ACHIEVEMENT_DATA_NAME], name);
  gAchievementData[id][E_ACHIEVEMENT_DATA_REQUIREMENT] = requirement;
  strpack(gAchievementData[id][E_ACHIEVEMENT_DATA_DESCRIPTION], description);
  return Achievement: gAchievementPoolSize++;
}

stock bool: Achievement_IsValid(Achievement: id) {
  return UCMP(_: id, gAchievementPoolSize);
}

stock bool: Achievement_GetName(Achievement: id, string: name[], length = sizeof(name)) {
  return Achievement_IsValid(id) && !!strunpack(name, gAchievementData[_: id][E_ACHIEVEMENT_DATA_NAME], length);
}

stock Achievement_GetRequirement(Achievement: id) {
  return !Achievement_IsValid(id) ? 0 : gAchievementData[_: id][E_ACHIEVEMENT_DATA_REQUIREMENT];
}

stock bool: Achievement_GetDescription(Achievement: id, string: description[], length = sizeof(description)) {
  return Achievement_IsValid(id) && !!strunpack(description, gAchievementData[_: id][E_ACHIEVEMENT_DATA_DESCRIPTION], length);
}

stock Achievement_GetPoolSize() {
  return gAchievementPoolSize;
}

#include "achievement-player"
