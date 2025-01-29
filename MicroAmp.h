// ==================================| Third Party Node Template |==================================

#pragma once
#include <JuceHeader.h>

namespace project
{
using namespace juce;
using namespace hise;
using namespace scriptnode;

// ==========================| The node class with all required callbacks |==========================

template <int NV> struct MicroAmp: public data::base
{
	// Metadata Definitions ------------------------------------------------------------------------
	
	SNEX_NODE(MicroAmp);

	double VinL = 0.0;
	double VinR = 0.0;
	
	double VoutL = 0.0;
	double VoutR = 0.0;

	double Fs = 0.0;			// sampling frequency
	double Ts = 0.0;			// Sampling time

	// Parameters
	double P5_value = 500e3;       //500K pot
	double P5_alpha = 0;     //position of pot
	double P5 = 0;
	double R6 = 2.7e3;       //2.7k
	double R4 = 56e3;        //56k
	double R9 = 470;         //470r
	double R10 = 10e3;       //10k

	double C2 = 4.7e-11;      //47pF
	double CR2 = 0;  //Capacitor Resistance
	double CX2L = 0;          //Capacitor State
	double CX2R= 0;          //Capacitor State

	double C3 = 4.7e-6;       //4.7uF
	double CR3 = 0;  //Capacitor Resistance
	double CX3L = 0;          //Capacitor State
	double CX3R = 0;          //Capacitor State

	double C5 = 15e-6;        //15uF
	double CR5 = 0;  //Capacitor Resistance
	double CX5L = 0;          //Capacitor State
	double CX5R = 0;          //Capacitor State


	double a0=0;
	double a1=0;
	double a2=0;

	double b0=0;
	double b1=0;

	double c0=0;
	double c1=0;

	double d0=0;
	double d1=0;

	double VxL=0;
	double VinBL=0;
	double VxAL=0;
	double VxR=0;
	double VinBR=0;
	double VxAR=0;
	
	struct MetadataClass
	{
		SN_NODE_ID("MicroAmp");
	};
	
	// set to true if you want this node to have a modulation dragger
	static constexpr bool isModNode() { return false; };
	static constexpr bool isPolyphonic() { return NV > 1; };
	// set to true if your node produces a tail
	static constexpr bool hasTail() { return false; };
	// set to true if your doesn't generate sound from silence and can be suspended when the input signal is silent
	static constexpr bool isSuspendedOnSilence() { return false; };
	// Undefine this method if you want a dynamic channel count
	static constexpr int getFixChannelAmount() { return 2; };
	
	// Define the amount and types of external data slots you want to use
	static constexpr int NumTables = 0;
	static constexpr int NumSliderPacks = 0;
	static constexpr int NumAudioFiles = 0;
	static constexpr int NumFilters = 0;
	static constexpr int NumDisplayBuffers = 0;
	
	// Scriptnode Callbacks ------------------------------------------------------------------------
	
	void prepare(PrepareSpecs specs)
	{
		Fs = specs.sampleRate;
		Ts = 1.0/Fs;

		CR2 = Ts/(2.0*C2);  //Capacitor Resistance
		CR3 = Ts/(2.0*C3);  //Capacitor Resistance
		CR5 = Ts/(2.0*C5);  //Capacitor Resistance


	}
	
	void reset()
	{
		
	}
	
	void handleHiseEvent(HiseEvent& e)
	{
		
	}
	
	template <typename T> void process(T& data)
	{
		
		static constexpr int NumChannels = getFixChannelAmount();
		// Cast the dynamic channel data to a fixed channel amount
		auto& fixData = data.template as<ProcessData<NumChannels>>();
		
		// Create a FrameProcessor object
		auto fd = fixData.toFrameData();
		
		while(fd.next())
		{
			VinL = fd[0];
			VinR = fd[1];

			// Transfer Function
			VoutL=(1.0/(CR5*a1*a2))*(((VinL*c1)/c0)-(CX3L/(P5*b0*b1*c0))-(CX5L*CR5)-(CX2L/c0));
			VoutR=(1.0/(CR5*a1*a2))*(((VinR*c1)/c0)-(CX3R/(P5*b0*b1*c0))-(CX5R*CR5)-(CX2R/c0));

			//VoutL = VinL*P5_alpha;
			//VoutR = VinR*P5_alpha;

			fd[0] = VoutL;
			fd[1] = VoutR;
			// Forward to frame processing
			processFrame(fd.toSpan());

			// Variables needed for Capacitor State Update
			VxL=(VoutL*CR5*a1*a2)+(CX5L*CR5);
  			VinBL=(VinL/(P5*d0*d1))+((CX3L*R6)/d1);
  			VxAL=VoutL*a0;

			VxR=(VoutR*CR5*a1*a2)+(CX5R*CR5);
  			VinBR=(VinR/(P5*d0*d1))+((CX3R*R6)/d1);
  			VxAR=VoutR*a0;

			// Capacitor State Update
			CX2L = (2.0/CR2) * (VinL - VxL) - CX2L;
  			CX3L = (2.0/CR3) * (VinBL) - CX3L;
  			CX5L = (2.0/CR5) * (VxL - VxAL) - CX5L;

			CX2R = (2.0/CR2) * (VinR - VxR) - CX2R;
  			CX3R = (2.0/CR3) * (VinBR) - CX3R;
  			CX5R = (2.0/CR5) * (VxR - VxAR) - CX5R;

		}
		
	}
	
	template <typename T> void processFrame(T& data)
	{
		
	}
	
	int handleModulation(double& value)
	{
		
		return 0;
		
	}
	
	void setExternalData(const ExternalData& data, int index)
	{
		
	}
	// Parameter Functions -------------------------------------------------------------------------
	
	template <int P> void setParameter(double v)
	{
		if (P == 0)
		{
			P5_alpha = (double)v;	
			// This will be executed for MyParameter (see below)
			jassertfalse;
		}

		P5 = P5_value*P5_alpha;

		a0=((R9/R10)+1.0);
		a1=((1.0/R9)+(1.0/CR5));
		a2=(a0-(1.0/(R9*a1)));

		b0=(1.0/CR3)+(1.0/R6);
		b1=(1.0+(R6/P5)-(1.0/R6*b0));

		c0=((1.0/CR2)+(1.0/R4));
		c1=(1.0/P5)-(R6/(P5*P5*b1))+(1.0/CR2)+(1.0/R4);

		d0=(1.0/R6+1.0/P5);
		d1=(R6/CR3)+1.0-(1.0/(R6*d0));
		
	}
	
	void createParameters(ParameterDataList& data)
	{
		{
			// Create a parameter like this
			parameter::data p("MyParameter", { 0.0, 1.0 });
			// The template parameter (<0>) will be forwarded to setParameter<P>()
			registerCallback<0>(p);
			p.setDefaultValue(0.5);
			data.add(std::move(p));
		}
	}
};
}


