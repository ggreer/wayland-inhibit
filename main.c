#include <assert.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define WLR_USE_UNSTABLE
#include <wayland-client.h>
#include <wlr/types/wlr_idle.h>
#include <wlr/types/wlr_idle_inhibit_v1.h>

void cleanup (int sig) {
  // no-op. just silently handle signal so pause() works
}

int main () {
  printf("Inhibiting idle...\n");
  struct wl_display *display = wl_display_connect(NULL);
  assert(display);

  struct wlr_idle_inhibit_manager_v1 *manager = wlr_idle_inhibit_v1_create(display);
  assert(manager);

  printf("Idle inhibited.\n");
  // Wait until a quit signal before cleaning up
  signal(SIGINT, cleanup);
  pause();

  // destroy idle inhibitor
  printf("Uninhibiting idle...\n");
  wlr_idle_inhibit_v1_destroy(manager);
  printf("Done.\n");
  return 0;
}
