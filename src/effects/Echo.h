/**********************************************************************

  Audacity: A Digital Audio Editor

  Echo.h

  Dominic Mazzoni
  Vaughan Johnson (dialog)

**********************************************************************/

#ifndef __AUDACITY_EFFECT_ECHO__
#define __AUDACITY_EFFECT_ECHO__

#include "StatefulPerTrackEffect.h"
#include "../ShuttleAutomation.h"
#include <float.h> // for FLT_MAX

class ShuttleGui;

using Floats = ArrayOf<float>;


struct EffectEchoSettings
{
   static constexpr double delayDefault = 1.0;
   static constexpr double decayDefault = 0.5;

   double delay{ delayDefault };
   double decay{ decayDefault };
};

class EffectEcho final : public StatefulPerTrackEffect
{
public:

   static inline EffectEchoSettings*
      FetchParameters(EffectEcho& e, EffectSettings&) { return &(e.mSettings); }
   
   static const ComponentInterfaceSymbol Symbol;

   EffectEcho();
   virtual ~EffectEcho();

   // ComponentInterface implementation

   ComponentInterfaceSymbol GetSymbol() const override;
   TranslatableString GetDescription() const override;
   ManualPageID ManualPage() const override;

   // EffectDefinitionInterface implementation

   EffectType GetType() const override;

   unsigned GetAudioInCount() const override;
   unsigned GetAudioOutCount() const override;

   // Effect implementation
   std::unique_ptr<EffectUIValidator> PopulateOrExchange(
      ShuttleGui & S, EffectSettingsAccess &access) override;

   struct Validator;

   struct Instance;

   std::shared_ptr<EffectInstance> MakeInstance(EffectSettings& settings) const;


private:
   // EffectEcho implementation

   EffectEchoSettings mSettings;


   const EffectParameterMethods& Parameters() const override;

#if 0
   // TODO simplify like this in C++20
   using ParametersType = CapturedParameters<EffectEcho,
        EffectParameter{
         &EffectEcho::delay, L"Delay",   1.0f, 0.001f,  FLT_MAX, 1.0f }
      , EffectParameter{
         &EffectEcho::decay, L"Decay",   0.5f, 0.0f,    FLT_MAX, 1.0f }
   >;
#else

static constexpr EffectParameter Delay{ &EffectEchoSettings::delay,
   L"Delay",   EffectEchoSettings::delayDefault, 0.001f,  FLT_MAX, 1.0f };
static constexpr EffectParameter Decay{ &EffectEchoSettings::decay,
   L"Decay",   EffectEchoSettings::decayDefault, 0.0f,    FLT_MAX, 1.0f };

#endif
};

#endif // __AUDACITY_EFFECT_ECHO__
