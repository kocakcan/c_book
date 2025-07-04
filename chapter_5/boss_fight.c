#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_HP	100

typedef struct {
	char *name;
	int hp;
	int max_damage;
} Character;

void print_status(Character *c) {
	printf("%s's HP: %d\n", c->name, c->hp);
}

int attack(Character *attacker, Character *defender) {
	int damage = rand() % attacker->max_damage + 1;
	defender->hp -= damage;
	if (defender->hp < 0) defender->hp = 0;
	printf("%s attacks %s for %d damage!\n", attacker->name, defender->name, damage);
	return damage;
}

int is_alive(Character *c) {
	return c->hp > 0;
}

int main(void) {
	srand(time(NULL));

	Character player = {"Chosen Undead", MAX_HP, 25};
	Character boss = {"Manus, Father of the Abyss", MAX_HP + 50, 20};

	printf("🔥 A dark fog rises...\n");
	printf("⚔️  %s enters the fog gate...\n", player.name);
	printf("👹 %s emerges from the abyss!\n\n", boss.name);	
	while (is_alive(&player) && is_alive(&boss)) {
		print_status(&player);
		print_status(&boss);
		printf("\n");

		attack(&player, &boss);
		if (!is_alive(&boss)) break;
		
		attack(&boss, &player);
		printf("-----------\n");
	}

	if (is_alive(&player))
		printf("\n🏆 Victory! %s has slain %s!\n", player.name, boss.name);
	else
		printf("\n💀 You Died. %s has fallen to %s...\n", player.name, boss.name);

	return 0;
}
