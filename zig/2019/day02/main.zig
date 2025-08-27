const std = @import("std");
const egg = @import("EggUtils.zig");

pub fn main() !void {
    const lines = try egg.read_file_lines("input.txt");
    const tokens = egg.tokenize_string(lines.items[0], ",");

    var intcode = std.ArrayList(usize).init(std.heap.page_allocator);
    for (tokens.items[0..tokens.items.len]) |str| {
        try intcode.append(try std.fmt.parseInt(usize, str, 10));
    }


    for (0..100) |noun| {
        for (0..100) |verb| {
            var ints = try intcode.clone();
            var halt: bool = false;
            var ip: usize = 0;

            ints.items[1] = noun;
            ints.items[2] = verb;

            while(!halt) {
                const args: []usize = ints.items[ip + 1..];

                switch (ints.items[ip]) {
                    1 => {
                        ints.items[args[2]] = ints.items[args[0]] + ints.items[args[1]];
                        ip += 4;
                    },
                    2 => {
                        ints.items[args[2]] = ints.items[args[0]] * ints.items[args[1]];
                        ip += 4;
                    },
                    99 => { 
                        halt = true; 
                        ip += 1;
                    },
                    else => unreachable
                }
            }

            if (ints.items[0] == 19690720) {
                std.debug.print("output: {d}\n", .{100 * noun + verb});
            }

        }
    }


}

fn print_ints(ints: std.ArrayList(usize), ip: usize) void {
    for (ints.items[0..ints.items.len - 1], 0..) |int, i| {
        if(ip == i) {
            std.debug.print("|{d}|,", .{int});
        } else {
            std.debug.print("{d},", .{int});
        }
    }
    std.debug.print("{d}\n", .{ints.getLast()});
}
