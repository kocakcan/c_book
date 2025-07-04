#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_HP		100
#define ESTUS_HEAL	30
#define ESTUS_USES	2
#define ROLL_CHANCE	50	/* 50% chance to dodge */
#define CRIT_CHANCE	20	/* 20% chance for critical hit */

typedef struct {
	char *name;
	int hp;
	int max_damage;
	int estus;
	int rolled;		/* flag to indicate roll success */
} Character;

void print_status(Character *c) {
	printf("%s - HP: %d | Estus: %d\n", c->name, c->hp, c->estus);
}

int is_alive(Character *c) {
	return c->hp > 0;
}

int random_percent(void) {
	return rand() % 100;
}

void attack(Character *attacker, Character *defender) {
	int crit = (random_percent() < CRIT_CHANCE);
	int damage = rand() % attacker->max_damage + 1;
	if (crit) {
		damage *= 2;
		printf("💥 Critical hit! ");
	}
	if (defender->rolled) {
		printf("%s dodged the attack!\n", defender->name);
		defender->rolled = 0;	/* reset dodge */
		return;
	}

	defender->hp -= damage;
	if (defender->hp < 0) defender->hp = 0;

	printf("%s attacks %s for %d damage!\n", attacker->name, defender->name, damage);
}

void drink_estus(Character *c) {
	if (c->estus > 0) {
		c->hp += ESTUS_HEAL;
		if (c->hp > MAX_HP) c->hp = MAX_HP;
		c->estus--;
		printf("🧪 %s drinks Estus Flask and restores %d HP!\n", c->name, ESTUS_HEAL);
	} else {
		printf("❌ No Estus left!\n");
	}
}

void roll(Character *c) {
	if (random_percent() < ROLL_CHANCE) {
		printf("🌀 %s performs a perfect roll and will dodge the next attack!\n", c->name);
		c->rolled = 1;
	} else {
		printf("💢 %s tries to roll but stumbles!\n", c->name);
		c->rolled = 0;
	}
}

void player_turn(Character *player, Character *boss) {
	printf("\nYour turn:\n");
	printf("1. Attack\n");
	printf("2. Roll\n");
	printf("3. Drink Estus (%d left)\n", player->estus);
	printf("> ");

	int choice;
	scanf("%d", &choice);

	switch (choice) {
		case 1:
			attack(player, boss);
			break;
		case 2:
			roll(player);
			break;
		case 3:
			drink_estus(player);
			break;
		default:
			printf("Invalid choice. You hesitate...\n");
	}
}

int main(void) {
	srand(time(NULL));

	Character player = {"Chosen Undead", MAX_HP, 25, ESTUS_USES, 0};
	Character boss = {"Manus, Father of the Abyss", MAX_HP + 50, 20, 0, 0};

	printf("🔥 A dark fog rises...\n");
	printf("⚔️  %s enters the fog gate...\n", player.name);
	printf("👹 %s emerges from the abyss!\n\n", boss.name);	
	while (is_alive(&player) && is_alive(&boss)) {
		printf("\n--- BATTLE STATUS ---\n");
		print_status(&player);
		print_status(&boss);

		player_turn(&player, &boss);

		if (!is_alive(&boss)) break;
		printf("\n👹 %s's turn...\n", boss.name);
		attack(&boss, &player);
	}

	if (is_alive(&player))
		printf("\n🏆 Victory! %s has slain %s!\n", player.name, boss.name);
	else
		printf("\n💀 You Died. %s has fallen to %s...\n", player.name, boss.name);

	return 0;
}
