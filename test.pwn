#include <a_samp>

#include "achievement"

stock Achievement: Kill = INVALID_ACHIEVEMENT_ID,
  Achievement: Death = INVALID_ACHIEVEMENT_ID,
  Achievement: KillGrenade[3] = { INVALID_ACHIEVEMENT_ID, ... };

main() {
  Kill = Achievement_Define("Sangue em Minhas Mãos", 1, "Mate um jogador por qualquer meio.");
  Death = Achievement_Define("KO'd", 1, "Seja morto por um jogador por qualquer meio.");
  KillGrenade[0] = Achievement_Define("Fire in the Hole (I)", 10, "Mate 10 jogadores com granadas.");
  KillGrenade[1] = Achievement_Define("Fire in the Hole (II)", 30, "Mate 30 jogadores com granadas.");
  KillGrenade[2] = Achievement_Define("Fire in the Hole (III)", 50, "Mate 50 jogadores com granadas.");
}

public OnPlayerDeath(playerid, killerid, reason) {
  if (killerid != INVALID_PLAYER_ID) {
    Player_GiveAchievementProgress(killerid, Kill, 1);

    if (reason == WEAPON_GRENADE) {
      for (new i; i < sizeof(KillGrenade); i++) {
        Player_GiveAchievementProgress(killerid, KillGrenade[i], 1);
      }
    }
  }

  Player_GiveAchievementProgress(playerid, Death, 1);
}

public OnPlayerUnlockAchievement(playerid, Achievement: id) {
  static string: name[MAX_ACHIEVEMENT_NAME + 1],
    string: description[MAX_ACHIEVEMENT_DESCRIPTION + 1];

  Achievement_GetName(id, name);
  Achievement_GetDescription(id, description);

  SendClientMessage(playerid, -1, va_return("Conquista desbloqueada: \"%s\". (%s)", name, description));

  if (id == Kill) {
    GivePlayerMoney(playerid, 100);
    SetPlayerScore(playerid, GetPlayerScore(playerid) + 1);
  }
}
