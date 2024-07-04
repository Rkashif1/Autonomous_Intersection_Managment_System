library IEEE;

use IEEE.STD_LOGIC_1164.ALL;

use IEEE.NUMERIC_STD.ALL;



entity Car is

    Port (

        clk     : in STD_LOGIC;

        reset   : in STD_LOGIC;

        car_id  : in INTEGER;

        from    : in INTEGER;  -- 0: North, 1: South, 2: East, 3: West

        Destination: in INTEGER;  -- 0: North, 1: South, 2: East, 3: West

        proximity : in INTEGER;

        priority_car_id : out INTEGER;

        allow_pass : out STD_LOGIC

    );

end Car;


architecture Behavioral of Car is

    signal current_priority_car_id : INTEGER := -1;

    signal current_proximity : INTEGER := 11; -- Higher than max proximity

begin

    process(clk, reset)

    begin

        if reset = '1' then

            current_priority_car_id <= -1;

            current_proximity <= 11;

            allow_pass <= '0';

        elsif rising_edge(clk) then

            -- Check and update priority car

            if proximity < current_proximity then

                current_priority_car_id <= car_id;

                current_proximity <= proximity;

            end if;


            -- Output priority car ID and allow pass

            priority_car_id <= current_priority_car_id;

            if current_priority_car_id = car_id then

                allow_pass <= '1';

            else

                allow_pass <= '0';

            end if;

        end if;

    end process;

end Behavioral;
