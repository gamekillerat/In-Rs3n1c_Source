#pragma once

namespace Features {

	extern char* Status;
	extern std::string connstring;

	extern float accelerationfloat;
	extern float brakeforcefloat;
	extern float tractionfloat;
	extern float deformfloat;
	extern float upshiftfloat;
	extern float suspensionfloat;

	extern bool orbool;
	void OffRadar(bool toggle);

	extern bool AirStrike;
	void AirStrike1(bool toggle);

	void TorqueMult();
	extern float Torqueint;
	extern bool Torquemult;
	extern float Powerint;
	void PowerMult();
	extern float Lightint;
	void LightMult();
	extern float Breakfloat;
	void BreakForce(float force);

	extern bool Gravity;
	void GravityGun(bool toggle);

	extern bool Drift;
	void DriftMode(bool toggle);

	extern bool globe;

	extern int headfont;

	extern bool Rainbowmenu2;
	extern bool spacetheme;
	extern bool customtheme;

	extern bool NameESP;
	void NameTagESP(bool toggle);

	extern bool Trigger;
	void TriggerAim(bool toggle);

	extern bool supermanmode;

	extern bool ShootWeaponT;
	void ShootWeaponTank(bool toggle);

	extern bool ShootDump;
	void ShootDumpTruck(bool toggle);

	extern bool ShootHydra;
	void Shootthehydra(bool toggle);

	extern bool Shootadd;
	void Shootadder(bool toggle);

	extern bool ShootBuz;
	void ShootBuzzard(bool toggle);

	extern bool Rainb;
	void Rainbow(bool toggle);

	extern bool Rneon;
	void RainbowNeon(bool toggle);

	extern bool Rwheels;
	void RainbowWheels(bool toggle);

	extern bool DisplayFPS;
	void featureDisplayFPS(bool toggle);

	extern bool DisplayShowinfo;
	void FeatureDisplayShowInfo(bool toggle);

	extern bool ShowTalking;
	void ShowTalkingbool(bool toggle);

	extern bool ShootR;
	void ShootRocket(bool toggle);

	extern bool ShootT;
	void ShootTanks(bool toggle);

	extern bool ShootTankR;
	void ShootTankRounds(bool toggle);

	extern bool ShootBall;
	void ShootBalls(bool toggle);


	extern bool ShootMini;
	void ShootMiniGun(bool toggle);

	void UpdateLoop();

	extern int TimePD;

	extern int Levels[8000];

	extern int ExploCh;

	void PlaceObjectByHash(Hash hash, float x, float y, float z, float pitch, float roll, float yaw, float heading, int id);


	void Freezer(Player target);
	extern bool freezed[35];

	extern bool expmeel;
	extern bool fireammo;
	extern bool expammo;
	extern bool rbgun;

	void Expmeels();
	void Fireammos();
	void Expammos();
	void RBGuner(bool toggle);

	extern int number;

	Vehicle SpawnVehicle(char* modelg, Vector3 coords, bool tpinto, float heading);

	bool cstrcmp(const char* s1, const char* s2);

	extern bool Neverwanted;
	void NeverGetWanted(bool toggle);
	extern bool Neverwanted2;
	void NeverGetWanted2(bool toggle);
	void RequestControlOfid(DWORD netid);

	extern bool rainbowmenu;
	void Rainbowmenu(bool toggle);

	void NameChanger(char* value);

	extern bool RPLoop;
	extern int RPLoopDelay;
	void rpLoop();

	extern bool fastrun;
	extern bool RunFast1;
	extern bool fastrun2;
	extern bool fastswim;
	extern bool SwimFast1;
	extern float swimint;
	extern float runint;
	void RunFast(bool toggle);
	void RunFast2(float);
	void SwimFast(bool toggle);
	void SwimFast2(float);
	extern bool osk;
	extern bool superman;
	void OSKR(bool toggle);
	void Superman(bool toggle);
	extern bool SonicRun;
	void RunSonic(bool toggle);


	void SetRank(int rpvalue);
	extern bool shootcash;
	extern bool AttachDetach[35];

	extern bool playerGodMode;
	void GodMode(bool toggle);

	extern bool playerForceField;
	void ForceField(bool toggle);

	extern bool cargodmodebool;
	void cargodmode(bool toggle);

	extern bool speedmetorbool;
	void speedmetor(bool toggle);

	extern bool carlowerbool;
	void carlower(bool toggle);

	extern bool playersuperjump;
	void SuperJump();

	extern bool playersuperjumpUltra;
	void SuperJumpUltra();

	extern bool playerinvisibility;
	void Invisibility(bool toggle);

	extern bool playertenkped;
	void TenKPedMoney(bool toggle);

	extern bool playerfireloop[35];
	void FireLoop(Player target);

	extern bool playerwaterloop[35];
	void WaterLoop(Player target);

	extern bool playernoragdoll;
	void NoRagdoll(bool toggle);

	extern int playerWantedLevel;
	void ChangeWanted(int level);
	int GetWanted(Player player);

	extern bool savenewdrop2[35];
	void cashdrop2(Player target);
	extern bool savenewdrop21[35];
	void cashdrop21(Player target);

	extern int attachobj[100];
	extern int nuattach;
	void attachobjects2(char* object);

	void DeleteEntity(int Handle);

	extern bool dowbool;
	void DriveOnWater(bool toggle);

	extern bool infammo;
	void noreloadv(bool toggle);

	void SetMultipliers();

	extern int stealthloopr;

	extern bool isStealthLoop1;
	void stealthLoop1(bool toggle);

	extern bool isStealthLoop2;
	void stealthLoop2(bool toggle);

	extern float accelerationmultiplier;
	extern float brakesmultiplier;
	extern float suspensionseight;

	extern int boostspeed;

	extern bool rainbowcar;
	void RainbowCar(bool toggle);

	extern bool rainbowsmokecar;
	void RainbowSmokeCar(bool toggle);

	extern bool rainbowwheelscar;
	void RainbowWheelsCar(bool toggle);

	extern bool rainbowinteriorcar;
	void RainbowInteriorCar(bool toggle);

	extern bool DeathOffRadar;
	void deathoffradar(bool);

	extern bool rlbool;
	void HasPaintLoop(bool toggle);

	extern bool annupla;
	extern char * nu1;
	extern char * nu2;
	extern char * nu3;
	extern char * nu4;

	extern bool mobileRadio;
	void mobilevoid(bool toggle);

	extern int TimePD;
	extern int TimePD2;
	extern int TimePD3;
	extern int TimePD5;
	extern int TimePD6;
	extern int TimePD9;
	extern int TimePD10;
	extern int TimePD11;

	void LoadPlayerInfo(char* playerName, Player p);
	extern int l;
	extern int l1;
	extern int l2;
	extern int l3;
	extern int l4;
	extern int l5;
	extern int l6;

	void ramWithVeh(Player target);

	void doAnimation(char* anim, char* animid);

	extern bool isWalkingNoClip;
	void walkingNoClip();

	extern bool isNoClip;
	void noClip();

	extern bool controler;

	void RequestControlOfid(Entity netid);

	void RequestingControl(Entity e);
	void playAnimationPlayer(Player player, bool loop, char * dict, char * anim);


	extern bool enginealwaysonbool;
	void enginealwayson(bool toggle);
	void flipup();
	void maxvehicle();

	extern bool fuckedhandling[32];
	void fuckhandling(Player player);

	extern bool camshaker[32];
	void shakecam(Player target);

	extern bool exploder[32];
	void explodeloop(Player target);

	extern bool nightvisionbool;

	void clearanim();

	extern bool esper;
	void esp(Player target);

	void TinyPlayer(bool toggle);
	void changeplate();
	void trapcage(Ped ped);
	void trapall();

	extern bool betiny;

	extern float accelerationfloat;
	extern float brakeforcefloat;
	extern float tractionfloat;
	extern float deformfloat;
	extern float upshiftfloat;
	extern float suspensionfloat;
	extern bool vehiclegravitybool;

	void PTFXCALL(char *call1, char *call2, char *name);

	extern bool PTLoopedO[35];
	void PTLopperO(Player target);

	extern bool rapidfirer;
	void rapidmaker();

	extern bool explodepedsbool;
	void explodepeds();
	extern bool explodenearbyvehiclesbool;
	void explodenearbyvehicles();
	extern bool deletenearbyvehiclesbool;
	void deletenearbyvehicles();

	extern int amount;
	extern bool banked;
	extern bool giver;

	extern bool spawnincar;
	extern bool spawnmaxed;
	void spawn_vehicle(std::string vehicle);

	extern bool PTLooped;
	extern int reamount;
	extern bool StealthLooptoggler[35];
	extern std::string name;
	extern std::string pw;
	extern bool StealthLooptogglerall;

	extern bool CashDropRemotev2[32];
	void CashDropv2(Player target);

	extern bool isPlayerFriend(Player player, BOOL result);

	extern bool semigodmode;
	void SemiGodMode();

	extern bool Rainb;
	void Rainbow(bool toggle);

	extern bool isInfBoost;
	void InfiniteBoost(bool toggle);

	extern int stealthDelaydel;

	extern bool moneyrain2k;
	void RainMoney(bool toggle);

	extern int stealthDelay1;

	extern bool deletenearbyvehiclesbool;
	void deletenearbyvehicles();

	extern bool VALKYIREROCKET;
	void valkyirerocket(bool toggle);

	extern bool antifkk;

	extern bool AsteroidShower;
	void AsteroidShowerToggle(bool toggle);

	extern bool free_cam;
	void freecam(bool toggle);

	extern bool bomber;
	void bomber_mode(bool toggle);

	extern bool cargopall;
	void cargoPall(bool toggle);

	extern bool isRainRockets;
	void rainRockets(bool toggle);

	Hash $(std::string str);

	extern int amount;
	extern bool banked;
	extern bool toBank;
	extern bool toBank9;
	extern bool toBank5;

	extern bool spawnincar;
	extern bool spawnmaxed;

	char* CharKeyboard();

	int NumberKeyboard();

	extern bool isSPBypass;
	void SPBypass();

	extern bool semigodself;
	void SemiGodSelf();

	extern bool carjump;
	void carjumpon();

	void StatSetInt(char* stat, int value, BOOL save);
	void SetRank(int rpvalue);
	void RPCorrect(int rpvalue);
	void MaxStats();
	void UnliSnacks();
	void UnlockTattoos();
	void UnlockWpnColors();
	void UnlockClothings();
	void Unlockcars();

	void stealthSingle(int amount);

	extern int dropDelay;
	extern float DropZ;
	extern int DropAmount;
	extern bool CashDropSelfBoolv1;
	void CashDropSelfv1(bool toggle);
	extern bool CashDropSelfBoolv2;
	void CashDropSelfv2(bool toggle);

	void removeBankMoney(int amount);
	void removeCashMoney(int amount);

	void withdraw(int amount);
	void deposit(int amount);

	void SetRank(int rpvalue);
	void RPCorrect(int rpvalue);

	extern bool seatbelt;
	void seatBelt(bool toggle);

	void stealthSingle2(int amount);

	int RankKeyboard();

	extern bool isRequestControl;
	extern bool isClearTasks;
	extern bool isAntiVehControl;
	extern bool isAntiRagdoll;
	extern bool isAntiPTFX;
	extern bool isAntiExplosion;
	extern bool isAntiFire;
	extern bool isGiveWeapon;
	extern bool isRemoveWeapon;
	extern bool isChangeTime;
	extern bool isHornProtection;
	extern bool isChangeWeather;

	void antiRequestControl();
	void antiVehControl();
	void antiRagdoll();
	void antiPTFX();
	void antiClearPedTasks();
	void antiExplosion();
	void antiFire();
	void antiGiveWeapons();
	void antiRemoveWeapons();
	void antiChangeTime();
	void antiHornProtection();
	void antiChangeWeather();

	extern bool isCEOKickProtex;
	void antiCEOKick(bool toggle);

	extern bool isKickToFMProtex;
	void antiKickToFreemode(bool toggle);

	extern bool isSoundSpamProtex;
	void antiSoundSpam(bool toggle);

	extern bool isAntiAFK;
	void antiAFK(bool toggle);

	extern bool isCEOBanProtex;
	void antiCEOBan(bool toggle);

	extern bool isSendToJobProtex;
	void antiSendToJob(bool toggle);

	extern bool isKickToSPProtex;
	void antiKickToSP(bool toggle);

	extern bool isCrashProtex;
	void antiCrash(bool toggle);

	extern bool isTeleportProtex;
	void antiTeleport(bool toggle);

	extern bool isTransactionErrorProtex;
	void antiTransactionError(bool toggle);

	extern int tintCount;
	int getTintIndex();

	void changeMk2Tint();

	extern bool isGravityGun;

	extern bool isAutoFire;
	void autoFire();

	extern bool isBreatheFire;
	void breatheFire();

	extern bool isDriveItGun;
	void driveItGun();

	extern bool isNoRecoil;
	void recoil(bool toggle);

	extern bool isTeleportGun;
	void teleportGun(bool toggle);

	void SetName(const std::string& name);

	void teleportToWaypoint();
	void teleportToObjective();
	void teleportToLocation(Vector3 Coords);
	void teleportForward();

	extern bool isSpectatePlayer;
	void spectatePlayer(bool toggle);

	extern bool isHornBoost;
	void hornBoost();

	void RemoteTeleportAll(int location);
	void RemoteTeleport(int location);

	void sendInvite(int location);

	extern bool Spam[32];
	void DoSoundSpam(Player target);

	extern bool RemoteOTRBool[32];
	void RemoteOTR(Player target);

	extern int inviteIndex;

	extern bool unliorbital;
	void UnliOrbital();

	extern bool bypasssell;
	void BypassSell();

	extern bool isRevealPlayers;
	void revealPlayers();

	extern bool requestAnimClipset(char* animName);
	void setPlayerWalkingStyle(char* animName);

	extern bool repairnearbyvehiclesbool;
	void repairnearbyvehicles();

	extern bool upgradenearbyvehiclesbool;
	void upgradenearbyvehicles();

	extern bool deletenearbyvehiclesbool;
	void deletenearbyvehicles();

	extern bool hornnearbyvehiclesbool;
	void hornnearbyvehicles();

	extern bool launchnearbyvehiclesbool;
	void launchnearbyvehicles();

	extern bool explodenearbytiresbool;
	void explodenearbytires();

	extern bool isFlashRun;
	void flashRun();

	extern bool isMarkRoutePlayer;
	void markRoutePlayer();

	extern bool isMarkPlayerEnemy;
	void markPlayerEnemy();

	extern bool isMarkPlayerFriendly;
	void markPlayerFriendly();

	extern bool isDrawPlayerMarker;
	void drawPlayerMarker();

	void PTFXCALLO(char *call1, char *call2, char *name, Player target);

	extern bool isAutoRegHealth;
	void AutoRegHealth(bool toggle);

	extern bool isAutoRegArmour;
	void AutoRegArmour(bool toggle);

	extern bool isAutoCleanPlayer;
	void AutoCleanPlayer(bool toggle);

	extern bool isInstantBrake;
	void instantBrake();

	extern bool isWallDrive;
	void wallDrive();

	extern int stealth1Value;
	extern int stealth2Value;
	extern int removeValue;

	extern bool isRemoveMoney;
	void removeMoneyLoop(bool toggle);

	extern bool isSPSnow;
	void spSnow();

	void cleanSelf();
	void healSelf();
	void addArmour();
	void suicide();

	extern int playerAlpha;

	extern int speedRun;

	extern bool isRepairLoop;
	void repairLoop();

	extern bool isAirStrikeGun;
	void airStrikeGun();

	void teleportToNearbyCar();

	char* setPlayerName(int player, char* tag);

	extern bool isBlackout;
	void blackOut();

	extern bool isMoneyGun;
	void moneyGun();

	extern int menu_version;

	extern int intnumber;
	extern bool headerchanger;
	void Headerchanger(bool toggle);

	extern bool isStealthBanked;

	extern bool isLightningEffect;
	extern bool isClownEffect; 
	extern bool isClown2Effect;
	extern bool isFireworkEffect;
	extern bool isAlienEffect;
	extern bool isAlien2Effect;
	extern bool isElectricEffect;
	extern bool isElectric2Effect;
	extern bool isWaterEffect;
	extern bool isBloodEffect;
	extern bool isSmokeEffect;
	void ptfxPlayer(char* call1, char* call2, char* name, int bone);

	extern Vehicle spawnedVeh[1024];
	extern char* spawnedvehnames[1024];
	extern int spawnvehl;

	extern int TimePD1;

	extern bool moneydropL1;
	void MoneyDropL1(bool T);

	extern bool moneydropL2;
	void MoneyDropL2(bool T);

	extern bool moneydropL3;
	void MoneyDropL3(bool T);

	extern bool moneydropL4;
	void MoneyDropL4(bool T);

	extern bool moneydropL5;
	void MoneyDropL5(bool T);

	extern bool moneydropL6;
	void MoneyDropL6(bool T);

	extern int blamesingle_player;
	void BlamePlayerSelective();
	void BlamePlayer();

	void forceSuicide();
	void massSuicide();

	extern bool isGTABannerProtex;

	void disableMenuOnDeath();

	extern Hash defaultModel;

	extern bool Powermult;
	extern bool Lightmult;
	extern bool BreakForce1;

	void TorqueMult();
	extern float Torqueint;
	extern bool Torquemult;
	extern float Powerint;
	void PowerMult();
	extern float Lightint;
	void LightMult();

	extern int Brake2int;
	void BrakeMult();

	extern bool isRemoteNeverWanted[32];
	void RemoteNeverWanted(Player target);

	namespace Online {
		extern int selectedPlayer;
		void TeleportToPlayer(Player player);
	}
}
