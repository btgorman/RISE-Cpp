#7
#include <string>

enum {
	// Alternates
	WIREDATA_ID = 1000,
	LINECODE_ID = 1001,
	// PowerArcs
	CABLE_ID = 1100,
	DIRECTCONNECTION_ID = 1101,
	OVERHEADLINE_ID = 1102,
	TWOWINDINGTRANSFORMER_ID = 1103,
	// PowerNodes
	BUS_ID = 1200,
	LOAD_ID = 1201,
	SYNCHGENERATOR_ID = 1202,
	UTILITY_ID = 1203,
};

// Origin -----------------------------------------------------------------------------------

class Power {

	// Inputs
	std::string object_name;
	bool operational_status;
	int object_ID_number;
	// Outputs

public:
	Power(std::string object_name_in,
		bool operational_status_in,
		int object_ID_number_in) {

		object_name = object_name_in;
		operational_status = operational_status_in;
		object_ID_number = object_ID_number_in;
	}
};

// Intermediate -----------------------------------------------------------------------------

class PowerArc : public Power {

	// Inputs
	int from_bus_object_ID_number;
	int from_bus_component_ID_number;
	int to_bus_object_ID_number;
	int to_bus_component_ID_number;
	// Outputs
	float current_1_magnitude;
	float current_1_angle;
	float real_power_entering;
	float real_power_leaving;
	float reactive_power_entering;
	float reactive_power_leaving;

public:
	PowerArc(std::string object_name_in,
		bool operational_status_in,
		int object_ID_number_in,
		int from_bus_object_ID_number_in,
		int from_bus_component_ID_number_in,
		int to_bus_object_ID_number_in,
		int to_bus_component_ID_number_in) : Power(object_name_in, operational_status_in, object_ID_number_in) {

		from_bus_object_ID_number = from_bus_object_ID_number_in;
		from_bus_component_ID_number = from_bus_component_ID_number_in;
		to_bus_object_ID_number = to_bus_object_ID_number_in;
		to_bus_component_ID_number = to_bus_component_ID_number_in;
		current_1_magnitude = 0.0;
		current_1_angle = 0.0;
		real_power_entering = 0.0;
		real_power_leaving = 0.0;
		reactive_power_entering = 0.0;
		reactive_power_leaving = 0.0;
	}
};

class PowerNode : public Power {

	// Inputs
	float latitude;
	float longitude;
	// Outputs
	float LL_voltage;
	float voltage_1_magnitude;
	float voltage_1_angle;
	float voltage_1_pu;

public:
	PowerNode(std::string object_name_in,
		bool operational_status_in,
		int object_ID_number_in,
		float latitude_in,
		float longitude_in) : Power(object_name_in, operational_status_in, object_ID_number_in) {

		latitude = latitude_in;
		longitude = longitude_in;
		LL_voltage = 0.0;
		voltage_1_magnitude = 0.0;
		voltage_1_angle = 0.0;
		voltage_1_pu = 0.0;
	}
};

// Alternate ---------------------------------------------------------------------------------

class LineCode : public Power { // number_of_cables_in

	static const int COMPONENT_ID_NUMBER = 0; //todo

											  // Inputs
	float continuous_ampacity;
	float emergency_ampacity;
	float r_1;
	float r_0;
	float x_1;
	float x_0;
	// Outputs

public:
	LineCode(std::string object_name_in,
		bool operational_status_in,
		int object_ID_number_in,
		float continuous_ampacity_in,
		float emergency_ampacity_in,
		float r_1_in,
		float r_0_in,
		float x_1_in,
		float x_0_in) : Power(object_name_in, operational_status_in, object_ID_number_in) {

		continuous_ampacity = continuous_ampacity_in;
		emergency_ampacity = emergency_ampacity_in;
		r_1 = r_1_in;
		r_0 = r_0_in;
		x_1 = x_1_in;
		x_0 = x_0_in;
	}
};

class WireData : public Power {

	static const int COMPONENT_ID_NUMBER = 0; //todo

											  // Inputs required
	float phase_resistance_50_C;
	float phase_GMR;
	float phase_continuous_ampacity;
	float phase_emergency_ampacity;
	float phase_diameter;
	// Inputs optional
	float neutral_resistance_50_C;
	float neutral_GMR;
	float neutral_continuous_ampacity;
	float neutral_emergency_ampacity;
	float neutral_diameter;

public:
	WireData(std::string object_name_in,
		bool operational_status_in,
		int object_ID_number_in,
		float phase_resisistance_50_c_in,
		float phase_GMR_in,
		float phase_continuous_ampacity_in,
		float phase_emergency_ampacity_in,
		float phase_diameter_in) : Power(object_name_in, operational_status_in, object_ID_number_in) {

		phase_resistance_50_C = phase_resisistance_50_c_in;
		phase_GMR = phase_GMR_in;
		phase_continuous_ampacity = phase_continuous_ampacity_in;
		phase_emergency_ampacity = phase_emergency_ampacity_in;
		phase_diameter = phase_diameter_in;
		neutral_resistance_50_C = -1.0;
		neutral_GMR = -1.0;
		neutral_continuous_ampacity = -1.0;
		neutral_emergency_ampacity = -1.0;
		neutral_diameter = -1.0;
	}

	WireData(std::string object_name_in,
		bool operational_status_in,
		int object_ID_number_in,
		float phase_resisistance_50_c_in,
		float phase_GMR_in,
		float phase_continuous_ampacity_in,
		float phase_emergency_ampacity_in,
		float phase_diameter_in,
		float neutral_resisistance_50_c_in,
		float neutral_GMR_in,
		float neutral_continuous_ampacity_in,
		float neutral_emergency_ampacity_in,
		float neutral_diameter_in) : Power(object_name_in, operational_status_in, object_ID_number_in) {

		phase_resistance_50_C = phase_resisistance_50_c_in;
		phase_GMR = phase_GMR_in;
		phase_continuous_ampacity = phase_continuous_ampacity_in;
		phase_emergency_ampacity = phase_emergency_ampacity_in;
		phase_diameter = phase_diameter_in;
		neutral_resistance_50_C = neutral_resisistance_50_c_in;
		neutral_GMR = neutral_GMR_in;
		neutral_continuous_ampacity = neutral_continuous_ampacity_in;
		neutral_emergency_ampacity = neutral_emergency_ampacity_in;
		neutral_diameter = neutral_diameter_in;
	}
};

// PowerArc Branch ----------------------------------------------------------------------------

class Cable : public PowerArc {

	static const int COMPONENT_ID_NUMBER = 0; //todo

											  // Inputs
	int linecode_object_ID;
	int number_of_cables;
	float voltage_rating;
	float length;
	// Outputs

public:
	Cable(std::string object_name_in,
		bool operational_status_in,
		int object_ID_number_in,
		int from_bus_object_ID_number_in,
		int from_bus_component_ID_number_in,
		int to_bus_object_ID_number_in,
		int to_bus_component_ID_number_in,
		int linecode_object_ID_in,
		int number_of_cables_in,
		float voltage_rating_in,
		float length_in) : PowerArc(object_name_in, operational_status_in, object_ID_number_in, from_bus_object_ID_number_in, from_bus_component_ID_number_in, to_bus_object_ID_number_in, to_bus_component_ID_number_in) {

		linecode_object_ID = linecode_object_ID_in;
		number_of_cables = number_of_cables_in;
		voltage_rating = voltage_rating_in;
		length = length_in;
	}
};

class DirectConnection : public PowerArc {


};

class OverheadLine : public PowerArc {

	static const int COMPONENT_ID_NUMBER = 0; //todo

	bool kron_reduction;
	int wiredata_object_ID;
	int number_of_conductors;
	float length;
	float soil_resistivity;
	float x_1_coordinate;
	float x_2_coordinate;
	float x_3_coordinate;
	float x_4_coordinate;
	float h_1_coordinate;
	float h_2_coordinate;
	float h_3_coordinate;
	float h_4_coordinate;
};

class TwoWindingTransformer : public PowerArc {

	static const int COMPONENT_ID_NUMBER = 0; //todo

	bool tap_side;
	int number_of_taps;
	int from_bus_wiring;
	int to_bus_wiring;
	float power_rating;
	float from_bus_voltage_rating;
	float to_bus_voltage_rating;
	float min_tap;
	float max_tap;
	float r_percent;
	float x_percent;
	float tap_percent;
};

// PowerNode Branch ----------------------------------------------------------------------------

class Bus : public PowerNode {

	static const int COMPONENT_ID_NUMBER = 0; //todo

	float nominal_LL_voltage;
};

class Load : public PowerNode {

	static const int COMPONENT_ID_NUMBER = 0; //todo

	int wiring;
	int load_model;
	int pf_type;
	float power_rating;
	float min_pu_voltage;
	float pf_percent;
	float nominal_LL_voltage;
	float current_rating;
	float current_1_magnitude;
	float current_1_angle;
	float real_power;
	float reactive_power;
};

class SynchGenerator : public PowerNode {

	static const int COMPONENT_ID_NUMBER = 0; //todo

	bool stiffness;
	int wiring;
	int number_of_poles;
	int RPM_rating;
	float power_rating;
	float pf_percent;
	float nominal_LL_voltage;
	float current_1_magnitude;
	float current_1_angle;
	float real_power;
	float reactive_power;
};

class Utility : public PowerNode {

	static const int COMPONENT_ID_NUMBER = 0; //todo

	bool stiffness;
	float nominal_LL_voltage;
	float base_power;
	float voltage_angle;
	float short_circuit_3_phase;
	float short_citcuit_SLG;
	float r_1;
	float r_0;
	float x_1;
	float x_0;
	float current_1_magnitude;
	float current_1_angle;
};