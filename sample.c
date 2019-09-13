void Jump(void){ //function to move sprite vertically
	if(hitSpring == 0){
		Fall();
		if(stillFalling == 0){
			if(jumpCount < 25){
				spriteY--;
				jumpCount++;
				TIMER0_TAILR_R = TIMER0_TAILR_R + 75000;
			}
			if(jumpCount == 25){
				jumpCount = 0;
				TIMER0_TAILR_R = 5000000;	
			}
			if(jumpCount == 7){
				hitPlatform = 0;
			}
			if(jumpCount == 0){
			}
		}
		if(stillFalling == 1){
			if(TIMER0_TAILR_R > 1000000){
				TIMER0_TAILR_R = TIMER0_TAILR_R - 100000;
			}
		}
	}
	if(hitSpring == 1){
		if(jumpCount < 159){
			spriteY--;
			jumpCount++;
		}
		if(jumpCount == 159){
			hitSpring = 0;
			jumpCount = 0;
			TIMER0_TAILR_R = 5000000;
		}
	}
}

void Fall(void){
	if(jumpCount == 0){
		if(springFlag == 1){ //detect when to jump from spring
			if((spriteY + 2) == springY){
				if((doodleX + 14) >= springX){
					if((doodleX + 1) <= (springX + 9)){
						Sound_Jump();
						hitSpring = 1;
						TIMER0_TAILR_R = 500000;
						jumpCount = 0;
					}
				}
			}
		}
	}
	if(hitSpring == 0){ //detect when to jump from platform
		if(jumpCount == 0){
			for(i=0;i<8;i++){
				if (spriteY <= pf[i].y - 4){
					if(spriteY >= pf[i].y - 6){
						if((doodleX + 14) >= pf[i].x){
							if((doodleX + 1) <= (pf[i].x +20)){
								Sound_Jump();
								hitPlatform = 1;
								TIMER0_TAILR_R = 750000;
							}
						}
					}
				}
			}
		}
		if(hitSpring == 0){ //detect when to jump from monster
			if(jumpCount == 0){
				if(spriteY == (monsterArray[randomMonster]->y - monsterArray[randomMonster]->h + 1)){
					if((doodleX + 14) >= (monsterArray[randomMonster]->x + 1)){
						if((doodleX + 1) <= (monsterArray[randomMonster]->x + monsterArray[randomMonster]->w -1)){
							Sound_Jump();
							hitPlatform = 1;
							TIMER0_TAILR_R = 750000;
							monsterArray[randomMonster]->status = dead;
							monsterAlive = 0;
							KillMonster();
						}
					}
				}
			}
		}
		if(hitSpring == 0){
			if(jumpCount == 0){
				if(hitPlatform == 0){
					spriteY++; //gravity
					if(TIMER0_TAILR_R > 1500000){
						TIMER0_TAILR_R = TIMER0_TAILR_R - 400000;
					}
					stillFalling = 1;
				}
			}
			if(hitPlatform){
				stillFalling = 0;
			}
		}
	}
}
