module _3_1mux(a,b,c,y,MADD
); 
	input [7:0]a;
	input [7:0]b;
	input [7:0]c;
	input [1:0]MADD;
	output [7:0]y;
	reg [7:0]y;
	always@(a,b,c,MADD)
	begin
	case(MADD)
		2'b00: y[7:0]=a[7:0];
		2'b01: y[7:0]=b[7:0];
		2'b10: y[7:0]=c[7:0];
		default: y="XXXXXXXX";
	endcase
	end
endmodule
