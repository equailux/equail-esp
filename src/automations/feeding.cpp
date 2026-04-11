#include "feeding.h"
#include "./internal/feeding.h"
#include "ws.h"
#include "../sensors/hook.h"
#include "../actuators/motor.h"
#include "../actuators/servo.h"
#include <ArduinoJson.h>

//

namespace aut
{
    // --- Do the sequence then increment it
    enum class FeedingSequence
    {
        StartSequence,
        MoveMotorLeft,
        CheckMotorLeft,
        OpenFeedStorage,
        WaitRefillTime,
        CloseFeedStorage,
        OpenFeedDistributor,
        MoveMotorRight,
        CheckMotorRight,
        MoveMotorLeftLast,
        CheckMotorLeftLast,
        FinishSequence,
    };

    //

    bool feedingEnabled = true;
    int feedingThreshold = 50;
    int feedingRefillTime = 5000;
    int feedingRefillAlpha = 0;
    int feedingMotorPosition = 0;
    FeedingSequence feedingSequenceState = FeedingSequence::FinishSequence;
}

namespace aut::internal
{
    void onReadFeeding(JsonArray arr);
    void onReadLimitter(JsonArray arr);

    //

    void setupFeeding()
    {
        ws::onEvent("Feeding", ws::EventQuery::Create, onReadFeeding);
        ssr::onRead(onReadLimitter);
    }

    void loopFeeding()
    {
        if (!feedingEnabled) 
        {
            att::writeMotor(0);
        }
        
        if (feedingSequenceState == FeedingSequence::StartSequence)
        {
            att::writeMotor(-1);
            feedingSequenceState = FeedingSequence::MoveMotorLeft;
        }
        
        if (feedingSequenceState == FeedingSequence::CheckMotorLeft)
        {
            if (feedingMotorPosition == -1)
            {
                att::writeMotor(0);
                feedingSequenceState = FeedingSequence::OpenFeedStorage;
            }
        }
        
        if (feedingSequenceState == FeedingSequence::OpenFeedStorage)
        {
            att::writeServo(180);
            feedingRefillAlpha = millis();
            feedingSequenceState = FeedingSequence::WaitRefillTime;
        }
        
        if (feedingSequenceState == FeedingSequence::WaitRefillTime)
        {
            bool refilled = millis() - feedingRefillAlpha >= feedingRefillTime;
            feedingSequenceState = refilled ? FeedingSequence::CloseFeedStorage : feedingSequenceState;
        }
        
        if (feedingSequenceState == FeedingSequence::CloseFeedStorage)
        {
            att::writeServo(0);
            feedingSequenceState = FeedingSequence::OpenFeedDistributor;
        }
        
        if (feedingSequenceState == FeedingSequence::OpenFeedDistributor)
        {
            att::writeServo(359);
            feedingSequenceState = FeedingSequence::MoveMotorRight;
        }
        
        if (feedingSequenceState == FeedingSequence::MoveMotorRight)
        {
            att::writeMotor(1);
            feedingSequenceState = FeedingSequence::CheckMotorRight;
        }
        
        if (feedingSequenceState == FeedingSequence::CheckMotorRight)
        {
            feedingSequenceState = feedingMotorPosition == 1 ? FeedingSequence::MoveMotorLeftLast : feedingSequenceState;
        }
        
        if (feedingSequenceState == FeedingSequence::MoveMotorLeftLast)
        {
            att::writeMotor(-1);
            feedingSequenceState = FeedingSequence::CheckMotorLeftLast;
        }
        
        if (feedingSequenceState == FeedingSequence::CheckMotorLeftLast)
        {
            feedingSequenceState = feedingMotorPosition == -1 ? FeedingSequence::FinishSequence : feedingSequenceState;
        }
    }

    void onReadFeeding(JsonArray arr)
    {
        for (JsonObject obj : arr)
        {
            int level = obj["value"].as<int>();
            if (level > feedingThreshold) continue;
            feedingSequenceState = FeedingSequence::StartSequence;
        }
    }
    
    void onReadLimitter(JsonArray arr)
    {
        for (JsonObject obj : arr)
        {
            if (obj["name"].as<String>().equals("Limit Switch1"))
            {
                bool value = obj["value"].as<bool>();
                feedingMotorPosition = value ? -1 : feedingMotorPosition;
            }
            
            if (obj["name"].as<String>().equals("Limit Switch2"))
            {
                bool value = obj["value"].as<bool>();
                feedingMotorPosition = value ? 1 : feedingMotorPosition;
            }
        }
    }
}