// これは メイン DLL ファイルです。

#include "stdafx.h"
#include "NScci.h"


HMODULE	hScci = NULL;

NScci::NScci::NScci()
{

	if (hScci == NULL) {
		hScci = LoadLibraryA("scci.dll");
	}

	if (hScci == NULL) {
		::FreeLibrary(hScci);
		return;
	}

	SCCIFUNC getSoundInterfaceManager = (SCCIFUNC)(::GetProcAddress(hScci, "getSoundInterfaceManager"));
	if (getSoundInterfaceManager == NULL) {
		::FreeLibrary(hScci);
		return;
	}

	// サウンドインターフェースマネージャー取得
	SoundInterfaceManager_ = getSoundInterfaceManager();
	SoundInterfaceManager_->initializeInstance();
}

NScci::NScci::~NScci()
{
	this->!NScci();
}

NScci::NScci::!NScci()
{
	if (SoundInterfaceManager_ == NULL) {
		return;
	}
	else {

		// 一括開放する場合（チップ一括開放の場合）
		SoundInterfaceManager_->releaseAllSoundChip();

		// サウンドインターフェースマネージャーインスタンス開放
		// FreeLibraryを行う前に必ず呼び出ししてください
		SoundInterfaceManager_->releaseInstance();

		SoundInterfaceManager_ = NULL;

		::FreeLibrary(hScci);

	}
}

void NScci::NScci::reset()
{
	SoundInterfaceManager_->reset();
	//for (int i = 0; i < getInterfaceCount(); i++) {
		//NSoundInterface^ nsif = getInterface(i);
		//nsif->reset();
	//}
}

int NScci::NScci::getInterfaceCount()
{
	if (SoundInterfaceManager_ == nullptr) return 0;
	return SoundInterfaceManager_->getInterfaceCount();
}

String^ NScci::NScci::getcInterfaceNameFromInterfaceInfo(int iInterfaceNo)
{
	SCCI_INTERFACE_INFO* a = SoundInterfaceManager_->getInterfaceInfo(iInterfaceNo);
	array<byte>^ a1 = gcnew array<byte>(64);

	System::Text::Encoding^ enc = System::Text::Encoding::GetEncoding("Shift_JIS");
	System::Runtime::InteropServices::Marshal::Copy(IntPtr(a->cInterfaceName), a1, 0, a1->Length);

	return enc->GetString(a1); 
}

int NScci::NScci::getiSoundChipCountFromInterfaceInfo(int iInterfaceNo)
{
	SCCI_INTERFACE_INFO* a = SoundInterfaceManager_->getInterfaceInfo(iInterfaceNo);
	return a->iSoundChipCount;
}

NScci::NSoundInterface^ NScci::NScci::getInterface(int iInterfaceNo)
{
	SoundInterface* si = SoundInterfaceManager_->getInterface(iInterfaceNo);
	NSoundInterface^ nsi = gcnew NSoundInterface();
	nsi->SoundInterface_ = si;
	nsi->parentNScci = this;

	return nsi;
}

Boolean NScci::NScci::isBufferEmpty()
{
	BOOL ret = SoundInterfaceManager_->isBufferEmpty();
	return ret ? true : false;
}

void NScci::NScci::sendData()
{
	SoundInterfaceManager_->sendData();
}

NScci::NSoundInterface::NSoundInterface()
{
}

NScci::NSoundInterface::~NSoundInterface()
{
	this->!NSoundInterface();
}

NScci::NSoundInterface::!NSoundInterface()
{

}

Boolean NScci::NSoundInterface::isSupportLowLevelApi()
{
	BOOL ret = SoundInterface_->isSupportLowLevelApi();
	return ret ? true : false;
}

Boolean NScci::NSoundInterface::setData(array<Byte>^ pData, long dSendDataLen)
{
	pin_ptr<Byte> p = &pData[0];

	BOOL ret = SoundInterface_->setData(p, dSendDataLen);

	delete p;

	return ret ? true : false;
}

long    NScci::NSoundInterface::getData(array<Byte>^ pData, long dGetDataLen)
{
	pin_ptr<Byte> p = &pData[0];
	long ret = SoundInterface_->getData(p, dGetDataLen);
	delete p;
	return ret;
}


Boolean NScci::NSoundInterface::setDelay(long dDelay)
{

	BOOL ret = SoundInterface_->setDelay(dDelay);

	return ret ? true : false;
}

long NScci::NSoundInterface::getDelay()
{

	return SoundInterface_->getDelay();

}

Boolean NScci::NSoundInterface::reset()
{

	BOOL ret = SoundInterface_->reset();

	return ret ? true : false;
}

Boolean NScci::NSoundInterface::init()
{

	BOOL ret = SoundInterface_->init();

	return ret ? true : false;
}

long	NScci::NSoundInterface::getSoundChipCount() 
{
	return SoundInterface_->getSoundChipCount();
}

NScci::NSoundChip^ NScci::NSoundInterface::getSoundChip(long iInterfaceNo)
{
	SoundChip* sc = SoundInterface_->getSoundChip(iInterfaceNo);
	NSoundChip^ nsc = gcnew NSoundChip();
	nsc->SoundChip_ = sc;
	nsc->parentSoundInterface = this;

	return nsc;
}



NScci::NSoundChip::NSoundChip()
{
}

NScci::NSoundChip::~NSoundChip()
{
	this->!NSoundChip();
}

NScci::NSoundChip::!NSoundChip()
{

}

NScci::NSCCI_SOUND_CHIP_INFO^ NScci::NSoundChip::getSoundChipInfo()
{
	SCCI_SOUND_CHIP_INFO* ssci = SoundChip_->getSoundChipInfo();

	NSCCI_SOUND_CHIP_INFO^ nssci= gcnew NSCCI_SOUND_CHIP_INFO();
	nssci->SCCI_SOUND_CHIP_INFO_ = ssci;

	return nssci;
}

int NScci::NSoundChip::getSoundChipType()
{
	return SoundChip_->getSoundChipType();
}

Boolean NScci::NSoundChip::setRegister(long dAddr, long dData)
{
	BOOL ret = SoundChip_->setRegister(dAddr, dData);
	return ret ? true : false;
}

long NScci::NSoundChip::getRegister(long dAddr)
{
	return SoundChip_->getRegister(dAddr);
}

Boolean NScci::NSoundChip::init()
{
	BOOL ret = SoundChip_->init();
	return ret ? true : false;
}

long  NScci::NSoundChip::getSoundChipClock()
{
	return SoundChip_->getSoundChipClock();
}

long NScci::NSoundChip::getWrittenRegisterData(long addr)
{
	return SoundChip_->getWrittenRegisterData(addr);
}

Boolean NScci::NSoundChip::isBufferEmpty()
{
	BOOL ret = SoundChip_->isBufferEmpty();
	return ret ? true : false;
}






NScci::NSCCI_SOUND_CHIP_INFO::NSCCI_SOUND_CHIP_INFO()
{
}

NScci::NSCCI_SOUND_CHIP_INFO::~NSCCI_SOUND_CHIP_INFO()
{
	this->!NSCCI_SOUND_CHIP_INFO();
}

NScci::NSCCI_SOUND_CHIP_INFO::!NSCCI_SOUND_CHIP_INFO()
{

}

String^	NScci::NSCCI_SOUND_CHIP_INFO::getcSoundChipName()
{
	char* a = SCCI_SOUND_CHIP_INFO_->cSoundChipName;
	array<byte>^ a1 = gcnew array<byte>(64);

	System::Text::Encoding^ enc = System::Text::Encoding::GetEncoding("Shift_JIS");
	System::Runtime::InteropServices::Marshal::Copy(IntPtr(a), a1, 0, a1->Length);

	return enc->GetString(a1);
}

int		NScci::NSCCI_SOUND_CHIP_INFO::getiSoundChip()
{
	return SCCI_SOUND_CHIP_INFO_->iSoundChip;
}

long	NScci::NSCCI_SOUND_CHIP_INFO::getdClock()
{
	return SCCI_SOUND_CHIP_INFO_->dClock;
}

Boolean	NScci::NSCCI_SOUND_CHIP_INFO::getbIsUsed()
{
	BOOL ret = SCCI_SOUND_CHIP_INFO_->bIsUsed;
	return ret ? true : false;
}

long	NScci::NSCCI_SOUND_CHIP_INFO::getdBusID()
{
	return SCCI_SOUND_CHIP_INFO_->dBusID;
}

long	NScci::NSCCI_SOUND_CHIP_INFO::getdSoundLocation()
{
	return SCCI_SOUND_CHIP_INFO_->dSoundLocation;
}

array<int>^		NScci::NSCCI_SOUND_CHIP_INFO::getiCompatibleSoundChip()
{
	array<int>^ a1 = gcnew array<int>(2);
	a1[0] = SCCI_SOUND_CHIP_INFO_->iCompatibleSoundChip[0];
	a1[1] = SCCI_SOUND_CHIP_INFO_->iCompatibleSoundChip[1];

	return a1;
}

array<long>^	NScci::NSCCI_SOUND_CHIP_INFO::getdCompatibleClock()
{
	array<long>^ a1 = gcnew array<long>(2);
	a1[0] = SCCI_SOUND_CHIP_INFO_->dCompatibleClock[0];
	a1[1] = SCCI_SOUND_CHIP_INFO_->dCompatibleClock[1];

	return a1;
}
