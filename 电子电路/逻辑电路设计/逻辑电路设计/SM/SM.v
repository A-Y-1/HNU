module SM(clk,sm,sm_en);
	input clk,sm_en;
	output reg sm;
	always@(negedge clk) 
	begin
	if(sm_en) sm<=!sm;
	else ;
	end
endmodule
