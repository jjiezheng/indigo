struct POutput {
	float4 color 	: SV_TARGET0;
};

POutput ps(float4 position			: SV_POSITION) {
	POutput OUT;
	OUT.color = float4(1, 1, 1, 1);				
	return OUT;
}