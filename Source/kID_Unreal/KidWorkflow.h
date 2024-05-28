#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerHUDWidget.h"
#include "FloatingChallengeWidget.h"
#include "AgeGateWidget.h"
#include "UnavailableWidget.h"
#include "KidWorkflow.generated.h"

UCLASS()
class UKidWorkflow : public UObject
{
    GENERATED_BODY()

public:
    void Initialize(TFunction<void(bool)> Callback);
    void CleanUp();

    // workflows
    void StartKidSession(const FString& Location);
    void HandleExistingChallenge(const FString& ChallengeId);
    void StartKidSessionWithDOB(const FString& Location, const FString& DOB);
    void GetUserAge(const FString& Location, TFunction<void(bool, bool, const FString&)> Callback);
    void ValidateAge(TFunction<void(bool)> Callback);
    void GetDefaultPermissions(const FString& Location);
    void ShowConsentChallenge(const FString& ChallengeId, int32 Timeout, const FString& OTP, const FString& QRCodeUrl, TFunction<void(bool)> OnConsentGranted);
    void GetSessionPermissions(const FString& SessionId, const FString& ETag);
    void HandleProhibitedStatus();
    void AttemptTurnOnFeature(const FString& FeatureName, TFunction<void()> EnableFeature);
    void GenerateFeatureChallenge(FString& OutChallengeId, FString& OutQRCodeUrl, FString& OutOTP);
    void CheckForConsent(const FString& ChallengeId, FDateTime StartTime, int32 Timeout, TFunction<void(bool)> OnConsentGranted);

    // managing session local storage
    void SaveSessionInfo();
    bool GetSavedSessionInfo();
    void ClearSession();
    TSharedPtr<FJsonObject> FindPermission(const FString& FeatureName);

    // managing challenge id local storage
    bool HasChallengeId();
    void SaveChallengeId(const FString& InChallengeId);
    void ClearChallengeId();
    bool LoadChallengeId(FString& OutChallengeId);

     // UI Elements
    void ShowUnavailableWidget();
    void ShowAgeGate(TFunction<void(const FString&)> Callback);
    void ShowFloatingChallengeWidget(const FString& OTP, const FString& QRCodeUrl, TFunction<void(const FString&)> OnEmailSubmitted);
    void DismissChallengeWindow();
    void ShowDemoControls();
    void ShowPlayerHUD();
    void UpdateHUDText();

    // Feature-specific functions
    void AttemptTurnOnChat();
    void EnableChat();
     
    void SetTimerManager(FTimerManager& InTimerManager) { TimerManager = &InTimerManager; }
private:
    static bool bShutdown;

    FTimerHandle ConsentPollingTimerHandle;
    TSharedPtr<FJsonObject> SessionInfo;
    FString AuthToken;

    UPlayerHUDWidget* PlayerHUDWidget;
    UFloatingChallengeWidget* FloatingChallengeWidget;
    UAgeGateWidget* AgeGateWidget;
    UUnavailableWidget* UnavailableWidget;
    FTimerManager* TimerManager;
};