module PC(clk,pc_ld,pc_in,a,add);
	input clk,pc_ld,pc_in;
	input [7:0] a;
	output[7:0] add;
	reg [7:0] add;
	always@(negedge clk)
	begin
		if(pc_in&&!pc_ld) add[7:0]<=add[7:0]+8'b00000001;
		else if(!pc_in&&pc_ld) add[7:0]<=a[7:0];
		else;
	end
endmodule
