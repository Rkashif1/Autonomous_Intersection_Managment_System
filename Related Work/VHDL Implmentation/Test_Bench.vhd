library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity Test_Bench is
end Test_Bench;

architecture Behavioral of Test_Bench is
    component Car is
        Port (
            clk     : in STD_LOGIC;
            reset   : in STD_LOGIC;
            car_id  : in INTEGER;
            from    : in INTEGER;
            Destination: in INTEGER;
            proximity : in INTEGER;
            priority_car_id : out INTEGER;
            allow_pass : out STD_LOGIC
        );
    end component;

    signal clk     : STD_LOGIC := '0';
    signal reset   : STD_LOGIC := '0';
    signal car_id  : INTEGER;
    signal from    : INTEGER;
    signal Destination: INTEGER;
    signal proximity : INTEGER;
    signal priority_car_id : INTEGER;
    signal allow_pass : STD_LOGIC;

    constant clk_period : time := 10 ns;

begin
    uut: Car
        Port map (
            clk => clk,
            reset => reset,
            car_id => car_id,
            from => from,
            Destination => Destination,
            proximity => proximity,
            priority_car_id => priority_car_id,
            allow_pass => allow_pass
        );

    clk_process : process
    begin
        clk <= '0';
        wait for clk_period/2;
        clk <= '1';
        wait for clk_period/2;
    end process;

    stim_proc: process
    begin
        -- Initialize Inputs
        reset <= '1';
        car_id <= 0;
        from <= 0;
        Destination <= 0;
        proximity <= 10;

        wait for 20 ns;

        reset <= '0';
        wait for 20 ns;

        -- Simulate car arrival
        car_id <= 1;
        from <= 0;  -- From NORTH
        Destination <= 1;    -- To SOUTH
        proximity <= 5;
        wait for 20 ns;

        car_id <= 2;
        from <= 1;  -- From SOUTH
        Destination <= 2;    -- To EAST
        proximity <= 3;
        wait for 20 ns;

        car_id <= 3;
        from <= 2;  -- From EAST
        Destination <= 3;    -- To WEST
        proximity <= 1;
        wait for 20 ns;

        car_id <= 4;
        from <= 3;  -- From WEST
        Destination <= 0;    -- To NORTH
        proximity <= 7;
        wait for 20 ns;

        wait;
    end process;
end Behavioral;
