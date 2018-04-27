// NScci.h

#pragma once
#include "scci.h"

using namespace System;

namespace NScci {

	public ref class NSCCI_SOUND_CHIP_INFO
	{
	public:
		NSCCI_SOUND_CHIP_INFO();
		~NSCCI_SOUND_CHIP_INFO();
		!NSCCI_SOUND_CHIP_INFO();

		SCCI_SOUND_CHIP_INFO* SCCI_SOUND_CHIP_INFO_;

		String^			getcSoundChipName();		// Sound Chip Name
		int				getiSoundChip();			// Sound Chip ID
		array<int>^		getiCompatibleSoundChip();	// Compatible Sound Chip ID
		long			getdClock();				// Sound Chip clock
		array<long>^	getdCompatibleClock();		// Sound Chip clock
		Boolean			getbIsUsed();				// Sound Chip Used Check
		long			getdBusID();				// 接続バスID
		long			getdSoundLocation();		// サウンドロケーション

	};

	ref class NSoundInterface;
	ref class NScci;

	public ref class NSoundChip
	{

	public:
		NSoundChip();
		~NSoundChip();
		!NSoundChip();

		SoundChip* SoundChip_;

		NSCCI_SOUND_CHIP_INFO^ getSoundChipInfo();
		int getSoundChipType();
		Boolean setRegister(long dAddr, long dData);
		long getRegister(long dAddr);
		Boolean init();
		long getSoundChipClock();
		long getWrittenRegisterData(long addr);
		Boolean isBufferEmpty();
		NSoundInterface^ parentSoundInterface;
	};

	public ref class NSoundInterface
	{

	public:
		NSoundInterface();
		~NSoundInterface();
		!NSoundInterface();
		NScci^ parentNScci;

		SoundInterface* SoundInterface_;

		Boolean isSupportLowLevelApi();
		Boolean setData(array<Byte>^ pData, long dSendDataLen);
		long    getData(array<Byte>^ pData, long dGetDataLen);
		Boolean setDelay(long dDelay);
		long    getDelay();
		Boolean reset();
		Boolean init();
		long	getSoundChipCount();
		NSoundChip^ getSoundChip(long dNum);
	};

	public ref class NScci
	{
		SoundInterfaceManager* SoundInterfaceManager_;
		SoundInterface* SoundInterface_;
		SoundChip* SoundChip_;

	public:
		NScci();
		~NScci();
		!NScci();

		int getInterfaceCount();

		String^ getcInterfaceNameFromInterfaceInfo(int iInterfaceNo);
		int getiSoundChipCountFromInterfaceInfo(int iInterfaceNo);
		NSoundInterface^ getInterface(int iInterfaceNo);
		void reset();
		Boolean isBufferEmpty();
		void sendData();
	};

}
