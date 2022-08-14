// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "HAL/Platform.h"

#include "CoreTypes.h"
#include "CoreGlobals.h"
#include "Templates/SharedPointer.h"
#include "IMediaTextureSample.h"
#include "Math/IntPoint.h"
#include "Math/Range.h"
#include "Misc/Timespan.h"
#include "MediaObjectPool.h"
#include "MediaSamples.h"
#include "MediaVideoDecoderOutputAndroid.h"

#include "RHI.h"
#include "RHIUtilities.h"

class FElectraTextureSampleSupport;

/**
 * Texture sample generated by AndroidMedia player.
 */
class FElectraTextureSample final
	: public IMediaTextureSample
	, public IMediaPoolable
	, public TSharedFromThis<FElectraTextureSample, ESPMode::ThreadSafe>
{
public:

	/** Default constructor. */
	FElectraTextureSample(TSharedPtr<FElectraTextureSampleSupport, ESPMode::ThreadSafe> InSupport)
	: Support(InSupport)
	, Texture(nullptr)
	, Buffer(nullptr)
	, BufferSize(0)
	{
	}

	/** Virtual destructor. */
	virtual ~FElectraTextureSample()
	{
		if (Buffer)
		{
			FMemory::Free(Buffer);
		}
	}

	void Initialize(FVideoDecoderOutput* InVideoDecoderOutput);

	virtual void InitializePoolable() override;
	virtual void ShutdownPoolable() override;

	//~ IMediaTextureSample interface

	virtual const void* GetBuffer() override
	{
		return Buffer;
	}

	virtual FIntPoint GetDim() const override
	{
		return VideoDecoderOutput->GetDim();
	}

	virtual FTimespan GetDuration() const override
	{
		return VideoDecoderOutput->GetDuration();
	}

	virtual double GetAspectRatio() const override
	{
		return VideoDecoderOutput->GetAspectRatio();
	}

	virtual EMediaOrientation GetOrientation() const override
	{
		return (EMediaOrientation)VideoDecoderOutput->GetOrientation();
	}

	virtual EMediaTextureSampleFormat GetFormat() const override
	{
		return EMediaTextureSampleFormat::CharBGRA;
	}

	virtual FIntPoint GetOutputDim() const override
	{
		return VideoDecoderOutput->GetOutputDim();
	}

	virtual uint32 GetStride() const override
	{
		return GetDim().X * sizeof(uint32);
	}

	virtual FRHITexture* GetTexture() const override
	{
		return Texture.GetReference();
	}

	virtual FMediaTimeStamp GetTime() const override
	{
		FDecoderTimeStamp Time = VideoDecoderOutput->GetTime();
		return FMediaTimeStamp(Time.Time, Time.SequenceIndex);
	}

	virtual bool IsCacheable() const override
	{
		return true;
	}

	virtual bool IsOutputSrgb() const override
	{
		return true;
	}

private:
	friend class FElectraTextureSampleSupport;

	void InitializeTexture();
	void SetupFromBuffer(const void* InBuffer, int32 InBufferSize);

	TSharedPtr<FElectraTextureSampleSupport, ESPMode::ThreadSafe> Support;

	TSharedPtr<FVideoDecoderOutputAndroid, ESPMode::ThreadSafe> VideoDecoderOutput;

	void* Buffer;
	int32 BufferSize;

	/** Texture resource. */
	TRefCountPtr<FRHITexture2D> Texture;
};


using FElectraTextureSamplePtr  = TSharedPtr<FElectraTextureSample, ESPMode::ThreadSafe>;
using FElectraTextureSampleRef  = TSharedRef<FElectraTextureSample, ESPMode::ThreadSafe>;

class ELECTRASAMPLES_API FElectraTextureSamplePool : public TMediaObjectPool<FElectraTextureSample, FElectraTextureSamplePool>
{
	using ParentClass = TMediaObjectPool<FElectraTextureSample, FElectraTextureSamplePool>;
	using TextureSample = FElectraTextureSample;

public:
	FElectraTextureSamplePool();

	TextureSample* Alloc() const
	{
		return new TextureSample(Support);
	}

	void PrepareForDecoderShutdown()
	{
	}

	void* GetCodecSurface();

private:
	TSharedPtr<FElectraTextureSampleSupport, ESPMode::ThreadSafe> Support;
};

