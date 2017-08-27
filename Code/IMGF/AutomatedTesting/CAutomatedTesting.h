#pragma once

#include "nsimgf.h"

class imgf::CAutomatedTesting
{
public:
	void						start(void);
	
private:
	// level 1
	
	void						testDataStreaming(void);
	void						testFormats(void);
	void						testFeatures(void);
	
	
	
	
	// level 2
	
	// data streaming
	void						testDataWriting(void);
	void						testDataReading(void);
	
	// formats
	void						testFormatsSerialization(void);
	void						testIntermediateFormatConversion(void);
	void						testOtherFormatInterfaces(void);
	
	// features
	void						testFeatures_open_and_close(void);
	void						testFeature_reopen(void);
	
	
	
	
	// level 3
	
	// formats
	void						testFormatSerialization(void);
};