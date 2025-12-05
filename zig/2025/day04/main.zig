const std = @import("std");

const allocator = std.heap.page_allocator;

// const grid_size: usize = 139;
const grid_size: usize = 139;
var buffer: usize = 0;

const offsets = [_]@Vector(2, i32){
    .{-1, -1}, .{-1, 0}, .{-1, 1},
    .{ 0, -1},           .{ 0, 1},
    .{ 1, -1}, .{ 1, 0}, .{ 1, 1},
};

const Coord = struct {
    x: i32,
    y: i32,

    pub fn init(x: i32, y: i32) Coord {
        return .{
            .x = x,
            .y = y
        };
    }
};

pub fn main() !void {
    const input = try read_lines("input.txt");
    // const input = try read_lines("test.txt");

    var grid: [2][grid_size][grid_size]bool = .{input, undefined};
    var to_check: [2]std.ArrayList(@Vector(2, i32)) = .{
        try .initCapacity(allocator, grid_size * grid_size),
        try .initCapacity(allocator, grid_size * grid_size)
    };

    for(0..grid_size) |x| {
        for(0..grid_size) |y| {
            to_check[buffer].appendAssumeCapacity(.{@intCast(x), @intCast(y)});
        }
    }

    var sum: i32 = 0;
    while(to_check[buffer].items.len != 0) {
        next_grid(&grid, &to_check, &sum);
    }  

    // for(0..grid_size) |x| {
    //     for(0..grid_size) |y| {
    //         std.debug.print("{s}", .{if (grid[x][y]) "#" else " "});
    //     }
    //     std.debug.print("\n", .{});
    // }

    std.debug.print("sum: {d}\n", .{sum});
}

pub fn next_grid(grids: *[2][grid_size][grid_size]bool, to_check: *[2]std.ArrayList(@Vector(2, i32)), sum: *i32) void {
    const op: usize = if (buffer == 0) 1 else 0;
    const read_grid = &grids[buffer];
    const write_grid = &grids[op];
    const read_to_check = &to_check[buffer];
    const write_to_check = &to_check[op];


    write_grid.* = read_grid.*;

    for(read_to_check.items) |next| {
        const x: usize = @intCast(next[0]);
        const y: usize = @intCast(next[1]);
        if(read_grid[x][y] and count_neighbors(read_grid, next) < 4) {
            sum.* += 1;
            write_grid[x][y] = false;

            for(offsets) |offset| {
                if(in_bounds(offset + next)) {
                    write_to_check.appendAssumeCapacity(@Vector(2, i32){offset[0] + next[0], offset[1] + next[1]});
                }
            }
        }
    }

    buffer = if (buffer == 0) 1 else 0;
}

pub fn in_bounds(coord: @Vector(2, i32)) bool {
    return coord[0] >= 0 and coord[0] < grid_size and coord[1] >= 0 and coord[1] < grid_size;
}

pub fn count_neighbors(grid: *const [grid_size][grid_size]bool, coord: @Vector(2, i32)) i32 {
    var count: i32 = 0;
    for (offsets) |offset| {
        const off = coord + offset;
        if(!in_bounds(off)) continue;

        count += if (grid[@intCast(off[0])][@intCast(off[1])]) 1 else 0;
    }
    return count;
}

pub fn copy_grid(grid: *[grid_size][grid_size]bool) [grid_size][grid_size]bool {
    var out: [grid_size][grid_size]bool = undefined;

    for(0..grid_size) |x| {
        std.mem.copyForwards(bool, &out[x], &grid[x]);
    }

    return out;
}

pub fn read_lines(file_name: []const u8) ![grid_size][grid_size]bool {
    var out: [grid_size][grid_size]bool = undefined;
    const file = std.fs.cwd().openFile(file_name, .{ .mode = .read_only }) catch |err| {
        std.debug.print("unable to open file at {s}", .{file_name});
        return err;
    };

    var buf: [1024 * 1024]u8 = undefined;
    var reader = file.reader(&buf);

    for(0..grid_size) |y| {
        const line = reader.interface.takeDelimiterExclusive('\n') catch { return out; };
        for(0..grid_size) |x| {
            out[x][y] = line[x] == '@';
        }
    }
    return out;
}
