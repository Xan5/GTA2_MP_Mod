const std = @import("std");

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{ .default_target = .{ .cpu_arch = .x86, .abi = .msvc } });
    const optimize = b.standardOptimizeOption(.{});

    const cflags = [_][]const u8{
        "-pedantic-errors",
        "-Wc++11-extensions",
        "-std=c++14",
        // "-g",
        "-Wmicrosoft-enum-forward-reference",
    };

    const injector = b.addExecutable(.{
        .name = "GTA2MP_Runner",
        .root_source_file = null,
        .target = target,
        .optimize = optimize,
    });
    injector.addCSourceFile(.{ .file = b.path("injector.cpp"), .flags = &cflags });
    injector.linkLibC();

    b.installArtifact(injector);

    const dll = b.addSharedLibrary(.{
        .name = "GTA2MP",
        .root_source_file = null,
        .target = target,
        .optimize = optimize,
    });

    var dir = try std.fs.cwd().openDir("src", .{ .iterate = true });
    var it = dir.iterate();
    while (try it.next()) |file| {
        if (file.kind != .file) {
            continue;
        }
        const l = file.name.len - 4;
        if (l >= 0 and std.mem.eql(u8, file.name[l..], ".cpp")) {
            const path = try std.fmt.allocPrint(b.allocator, "./src/{s}", .{file.name});
            dll.addCSourceFile(.{ .file = b.path(path), .flags = &cflags });
        }
    }
    dll.linkLibC();
    b.installArtifact(dll);

    const run_cmd = b.addRunArtifact(injector);
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}
