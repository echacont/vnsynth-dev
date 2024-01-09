// ELeonora Chacón Taylor 2024
// wavetable_top.v wavetable hardware description top file

`include "wavetable.vh"

module wavetable_top ( 
        input  i_clk, 
        input  i_reset,
		// Wishbone interface
		input  i_wb_cyc, 
        input  i_wb_stb, 
        input         i_wb_we, 
        input  [5:0]  i_wb_addr, 
        input  [31:0] i_wb_data,
		output reg o_wb_ack, 
        output o_wb_stall, 
        output reg [31:0] o_wb_data,
        // Pulse density modulation audio output
		output o_pwm, 
        output o_aux, 
        output o_int);

    // Wishbone register write enable
    wire reg_we = i_wb_cyc & i_wb_stb & i_wb_we & !o_wb_ack;
    
    always @(posedge i_clk) begin
        if (i_reset) begin
            o_wb_ack <= 0;
            o_wb_data <= 0;
       end
        else begin
            o_wb_ack <= i_wb_cyc & !o_wb_ack; // Always acknowledge
            // wram_we needs to be only a pulse
            wram_we <= 0;
            wram_en <= 0;

            // Wishbone write address decoder
            if (reg_we)
                case (i_wb_addr[5:2])
                    // control register
                    0: begin
                        wram_we   <= i_wb_data[0];
                        wram_en   <= 1;
                    end
                    // wavetable ram address
                    1: wram_addr <= i_wb_data[`WAVE_BRAM_DATA_WIDTH-1:0];
                    // wavetable ram data in
                    2: wram_di   <= i_wb_data[`WAVE_BRAM_DATA_WIDTH-1:0];
                endcase

            // Wishbone read address decoder
            if (~reg_we)
                case (i_wb_addr[5:2])
                    // status register 
                    0: o_wb_data <= 0;
                    // wavetable ram address
                    1: o_wb_data[`WAVE_BRAM_DATA_WIDTH-1:0] <= wram_addr;
                    // wavetable ram data out
                    2: o_wb_data[`WAVE_BRAM_DATA_WIDTH-1:0] <= wram_dout;
                endcase
            

        end // not reset
    end


    // Wavetable RAM signals
    wire [`WAVE_BRAM_DATA_WIDTH-1:0]  wram_dout;
    wire [`WAVE_BRAM_ADDR_WIDTH-1:0]  next_wram_addr;
    
    // registers
    reg   wram_we = 0;
    reg   wram_en;
    reg  [`WAVE_BRAM_DATA_WIDTH-1:0]  wram_di = 0;
    reg  [`WAVE_BRAM_ADDR_WIDTH-1:0]  wram_addr = 0;

    assign next_wram_addr = wram_addr+1;

    // BRAM instance
    rams_sp_nc wave_bram0 (
        .clk    (i_clk),
        .we     (wram_we),
        .en     (wram_en),
        .addr   (wram_addr),
        .di     (wram_di),
        .dout   (wram_dout));


endmodule

// elecha: using example code from Xilinx:
// Single-Port Block RAM No-Change Mode
// File: rams_sp_nc.v

module rams_sp_nc (clk, we, en, addr, di, dout);

input clk; 
input we; 
input en;
input [`WAVE_BRAM_ADDR_WIDTH-1:0] addr; 
input [`WAVE_BRAM_DATA_WIDTH-1:0] di; 
output [`WAVE_BRAM_DATA_WIDTH-1:0] dout;

reg [`WAVE_BRAM_DATA_WIDTH-1:0] RAM [`WAVE_BRAM_DATA_SIZE-1:0];
reg [`WAVE_BRAM_DATA_WIDTH-1:0] dout;

always @(posedge clk)
begin
  if (en)
  begin
    if (we)
      RAM[addr] <= di;
    else
      dout <= RAM[addr];
  end
end
endmodule
