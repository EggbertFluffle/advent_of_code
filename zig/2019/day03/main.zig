const std = @import("std");
const egg = @import("EggUtils.zig");

pub fn main() !void {
    const lines = try egg.read_file_lines("test.txt");
    const first = try parse_input(egg.tokenize_string(lines.items[0], ","));
    const second = try parse_input(egg.tokenize_string(lines.items[1], ","));

    const collisions = get_collisions(first, second);
}

fn get_collision(first: std.ArrayList(@Vector(2, i32)), second: std.ArrayList(@Vector(2, i32))) @Vector(2, i32) {
    for (1..first.items.len) |f| {
        for (1..second.items.len) |s| {
            
        }
    }
}

fn parse_input(instructions: std.ArrayList([]const u8)) !std.ArrayList(@Vector(2, i32)) {
    var out = try std.ArrayList(@Vector(2, i32)).initCapacity(std.heap.page_allocator, instructions.items.len);
    var pos: @Vector(2, i32) = .{ 0, 0 };
    
    for (instructions.items) |ins| {
        const dist = std.fmt.parseInt(i32, ins[1..], 10) catch |err| {
            std.debug.print("Cannot format string \"{!}\"", .{err});
            return err;
        };

        switch (ins[0]) {
            'U' => { pos[1] += dist; },
            'D' => { pos[1] -= dist; },
            'L' => { pos[0] -= dist; },
            'R' => { pos[0] += dist; },
            else => unreachable
        }

        try out.append(pos);
    }
    return out;
}
